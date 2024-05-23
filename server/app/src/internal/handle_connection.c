/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** handle_connection
*/

#include "serrorh.h"
#include "server.h"
#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#include <sys/select.h>
#include <unistd.h>

static void client_create(server_t *server, int client_sd)
{
    client_t client = {
        .delete = false,
        .sd = client_sd,
    };

    if (str_init(&client.read_buf, "") != BUF_OK) {
        LOG_ERROR("Failed to create client, read_buf");
        return;
    }
    if (str_init(&client.write_buf, "") != BUF_OK) {
        LOG_ERROR("Failed to create client, write_buf");
        return;
    }
    if (vec_push(&server->clients, &client) != BUF_OK) {
        close(client_sd);
        LOG_ERROR("Failed to create client, add to server");
    }
}

void server_accept(server_t *server)
{
    int client_sd = 0;
    socklen_t size = sizeof(server->addr);

    client_sd =
        accept(server->listen_sd, (struct sockaddr *) &server->addr, &size);
    if (client_sd < 0) {
        return;
    }
    LOG_INFO("New connection from %s:%d", inet_ntoa(server->addr.sin_addr),
        ntohs(server->addr.sin_port));
    client_create(server, client_sd);
}
