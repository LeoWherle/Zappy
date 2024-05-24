/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** execute
*/

#include "buffer.h"
#include "packets.h"
#include "serrorh.h"
#include "server.h"
#include "sstrings.h"
#include "trantor.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static size_t get_next_packet(string_t *buf, size_t start)
{
    size_t i = start;

    for (; i < buf->nmemb; i++) {
        if (((char *) buf->items)[i] == '\n') {
            return i + 1;
        }
    }
    return 0;
}

/**
 * @brief Sends the client the starting information
 * <-- CLIENT - NUM \n
 * <-- X Y \n
 */
static void client_send_start_info(
    client_t *client, player_t *player, unsigned int cnb)
{
    char msg[1024] = {0};

    if (player == NULL) {
        snprintf(msg, sizeof(msg), "0\n0 0\n");
    } else {
        snprintf(msg, sizeof(msg), "%d\n%d %d\n", cnb, player->coord[0],
            player->coord[1]);
        client->player = player;
    }
    if (str_push_bytes(&client->write_buf, msg, strlen(msg)) != BUF_OK) {
        LOG_ERROR("Failed to push start info to write buffer");
    }
}

/**
 * @brief Expect the client's team name
 * --> TEAM - NAME \n
 * <-- CLIENT - NUM \n
 * <-- X Y \n
 * @return the number of bytes used from the read buffer
 */
static size_t client_get_connection(server_t *server, client_t *client)
{
    char *data = client->read_buf.items;
    char *team_name = client->read_buf.items;
    size_t next_packet = 0;

    next_packet = get_next_packet(&client->read_buf, 0);
    if (!next_packet) {
        return 0;
    }
    data[next_packet - 1] = '\0';
    if (strcmp(team_name, "GRAPHIC")) {
        client->is_gui = true;
    } else {
        client->player = hatch_team_egg(&server->trantor, team_name);
        team_name = &data[next_packet];
        if (client->player == NULL) {
            LOG_DEBUG("Failed to find available team for client");
            client->delete = true;
        }
        client_send_start_info(client, client->player,
            count_team_egg(&(server->trantor), team_name));
    }
    return next_packet - 1;
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

static size_t client_process_data(client_t *client, player_t *player)
{
    size_t next_packet = 0;
    char *data = client->read_buf.items;

    next_packet = get_next_packet(&client->read_buf, 0);
    while (next_packet != 0) {
        data[next_packet - 1] = '\0';
        feed_player_line(player, data);
        next_packet = get_next_packet(&client->read_buf, next_packet);
    }
    return next_packet - 1;
}

size_t client_execute(client_t *client, server_t *server)
{
    if (!client->read_buf.nmemb) {
        return 0;
    }
    if (client->player == NULL) {
        if (!client->sent_welcome) {
            return client_send_welcome(client);
        } else {
            return client_get_connection(server, client);
        }
    } else {
        return client_process_data(client, client->player);
    }
}
