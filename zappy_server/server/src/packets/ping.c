/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** ping
*/

#include "serrorh.h"
#include "packets.h"
#include "server.h"

bool packet_ping(server_t *server, client_t *client,
    client_packet_t *packet, pck_server_user_t *result)
{
    (void) client;
    (void) server;
    (void) packet;
    LOG_INFO("Received ping command");
    result->type = SERVER_PONG;
    return true;
}
