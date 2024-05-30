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
static void cl_send_start(client_t *client, player_t *player, unsigned int cnb)
{
    if (player != NULL) {
        talkf(&client->write_buf, "%d\n%d %d\n",
            cnb, player->coord[0], player->coord[1]);
    }
    if (client->is_gui) {
        talk(&client->write_buf, "1\n0 0\n");
        return;
    }
    if (player == NULL) {
        talk(&client->write_buf, "0\n0 0\n");
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
    cl->player = hatch_team_egg(&srv->trantor, tname);
    if (cl->player == NULL) {
        LOG_DEBUG("Failed to find available team name %s for cl", tname);
        cl->delete = true;
    }
    cl_send_start(cl, cl->player, count_team_egg(&(srv->trantor), tname));
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
    if (strcmp(tname, "GRAPHIC") == 0)
        cl->is_gui = true;
    else
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

    if (str_push_bytes(&client->write_buf, msg, sizeof(msg)) == BUF_OK) {
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
    LOG_DEBUG("rbuf1: -%s-", data);
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
    if (player->response_buffer.nmemb == 0)
        return;
    if (str_push_str(&client->write_buf, &player->response_buffer) != BUF_OK)
        return;
    str_clear(&player->response_buffer);
}

size_t client_execute(client_t *client, server_t *server)
{
    if (client->player == NULL && !client->is_gui) {
        if (!client->sent_welcome) {
            return client_send_welcome(client);
        } else {
            return client_get_connection(server, client);
        }
    } else {
        client_process_output(client, client->player);
        return client_process_data(client, client->player, &server->trantor);
    }
}
