/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** ping
*/

#include "packets.h"
#include "serrorh.h"
#include "server.h"
#include "vector.h"
#include <string.h>

bool packet_login(UNUSED server_t *server, client_t *client,
    UNUSED client_packet_t *packet, UNUSED pck_server_user_t *result)
{
    LOG_INFO("Received login command");
    client->logged_in = true;
    return true;
}

bool packet_logout(UNUSED server_t *server, client_t *client,
    UNUSED client_packet_t *packet, pck_server_user_t *result)
{
    LOG_INFO("Received logout command");
    if (client->logged_in == false) {
        result->type = SERVER_ERROR_UNAUTHORIZED;
        return true;
    }
    result->type = SERVER_CONFIRM_LOGGED_OUT;
    client->logged_in = false;
    return true;
}
