/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** client_delete
*/

#include "serrorh.h"
#include "server.h"
#include "vector.h"
#include <unistd.h>

void client_teardown(client_t *client)
{
    if (client != NULL) {
        close(client->sd);
        vec_reset(&client->read_buf);
        vec_reset(&client->write_buf);
    }
}

void client_remove(client_t *client, server_t *server)
{
    ssize_t client_index = 0;

    client_teardown(client);
    client_index = vec_indexof(&server->clients, client);
    if (client_index < 0) {
        LOG_ERROR("Failed to find client in server");
        return;
    }
    if (vec_erase(&server->clients, (size_t) client_index, 1)) {
        LOG_WARN("Failed to remove client from server");
        return;
    }
}
