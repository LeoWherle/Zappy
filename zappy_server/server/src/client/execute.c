/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** execute
*/

#include "packets.h"
#include "serrorh.h"
#include "server.h"
#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static const packet_t packet_list[] = {
    [CLIENT_LOGIN] = {.name = "login", .handle = packet_login},
    [CLIENT_LOGOUT] = {.name = "logout", .handle = packet_logout},
    [CLIENT_PING] = {.name = "ping", .handle = packet_ping},
};

size_t client_execute(
    client_t *client, __attribute__((unused)) server_t *server)
{
    client_packet_t *packet = NULL;
    pck_server_user_t result = {0};

    if (client->read_buf.nmemb < sizeof(*packet))
        return 0;
    packet = client->read_buf.items;
    if (packet->type >= CLIENT_ENUM_COUNT) {
        LOG_ERROR("Invalid packet type: %d", packet->type);
        return 0;
    }
    if (packet_list[packet->type].handle(server, client, packet, &result)) {
        if (vec_append_array(&client->write_buf, &result, sizeof(result), 1)) {
            LOG_ERROR("Failed to push response to write buffer");
            return 0;
        }
        return sizeof(*packet);
    }
    LOG_ERROR("Failed to handle packet type: %d", packet->type);
    return 0;
}
