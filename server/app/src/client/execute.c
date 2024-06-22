/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** execute
*/

#include "buffer.h"
#include "serrorh.h"
#include "server.h"
#include "sstrings.h"
#include "trantor.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static int get_next_packet(string_t *buf, size_t start)
{
    char *newline =
        memchr(((char *) buf->items) + start, '\n', buf->nmemb - start);

    if (newline != NULL) {
        return (int) (newline - (char *) buf->items + 1);
    }
    return -1;
}

/**
 * @brief Sends the client the starting information
 * <-- CLIENT - NUM \n
 * <-- X Y \n
 */
static void cl_send_start(
    client_t *client, player_t *player, unsigned int cnb, map_t *map)
{
    if (player != NULL) {
        talkf(&client->write_buf,
            "%d\n%d %d\n", cnb, map->width, map->height);
    }
    if (client->is_gui) {
        talkf(&client->write_buf, "1\n%d %d\n", map->width, map->height);
        return;
    }
    if (player == NULL) {
        talk(&client->write_buf, "ko\n");
    }
}

/**
 * @brief Expect the client's team name
 * --> TEAM - NAME \n
 * <-- CLIENT - NUM \n
 * <-- X Y \n
 * @return the number of bytes used from the read buffer
 */
static void player_get_connection(
    server_t *srv, client_t *cl, const char *tname)
{
    player_t *p = hatch_team_egg(&srv->trantor, tname);

    if (p == NULL) {
        LOG_DEBUG("Failed to find available team name %s for cl", tname);
        cl->delete = true;
        return;
    }
    cl->player_id = p->n;
    cl_send_start(cl, p,
        count_team_egg(&(srv->trantor), tname), &srv->trantor.map);
}

/**
 * @brief Handles new clients, graphic or not
 * Expect the client's team name
 *
 * @return the number of bytes used from the read buffer
 */
static size_t client_get_connection(server_t *srv, client_t *cl)
{
    char *data = cl->read_buf.items;
    char *tname = cl->read_buf.items;
    int next_packet = 0;

    next_packet = get_next_packet(&cl->read_buf, 0);
    if (next_packet <= 0)
        return 0;
    data[next_packet - 1] = '\0';
    if (strcmp(tname, "GRAPHIC") == 0) {
        cl->is_gui = true;
        trantor_log_players(&srv->trantor);
    } else
        player_get_connection(srv, cl, tname);
    return next_packet;
}

/**
 * @brief Gives a warm welcome to the client
 * <-- WELCOME \n
 * @return nothing as we don't process what the clients sends
 */
static size_t client_send_welcome(client_t *client)
{
    char msg[] = "WELCOME\n";

    if (str_push_bytes(&client->write_buf, msg, strlen(msg)) == BUF_OK) {
        client->sent_welcome = true;
        return 0;
    }
    LOG_ERROR("Failed to push welcome message to write buffer");
    return 0;
}

static size_t client_process_data(
    client_t *client, player_t *player, trantor_t *trantor)
{
    int next_packet = 0;
    char *data = client->read_buf.items;

    next_packet = get_next_packet(&client->read_buf, 0);
    if (next_packet <= 0)
        return 0;
    data[next_packet - 1] = '\0';
    if (client->is_gui) {
        gui_feed_trantor_line(trantor, data);
    } else {
        feed_player_line(player, data);
    }
    data[next_packet - 1] = '\n';
    return next_packet;
}

// simply takes whats in player->response buffer and puts its in the client one
static void client_process_output(client_t *client, player_t *player)
{
    if (player->is_egg || player->response_buffer.nmemb == 0)
        return;
    if (str_push_str(&client->write_buf, &player->response_buffer) != BUF_OK)
        return;
    str_clear(&player->response_buffer);
}

static void gui_client_process_output(client_t *client, trantor_t *trantor)
{
    if (trantor->log.nmemb == 0)
        return;
    if (str_push_str(&client->write_buf, &trantor->log) != BUF_OK)
        return;
    str_clear(&trantor->log);
}

// WARNING : For now vec_at is ok, because we don't delete dead players
size_t client_execute(client_t *client, server_t *server)
{
    player_t *player = NULL;

    if (client->player_id == 0 && !client->is_gui) {
        if (!client->sent_welcome) {
            return client_send_welcome(client);
        } else {
            return client_get_connection(server, client);
        }
    }
    if (client->is_gui) {
        gui_client_process_output(client, &server->trantor);
    } else {
        player = vec_at(&server->trantor.players, client->player_id - 1);
        client_process_output(client, player);
    }
    return client_process_data(client, player, &server->trantor);
}
