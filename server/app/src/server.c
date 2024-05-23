/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** server
*/

#include "server.h"
#include "common.h"
#include "serrorh.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int server_init(server_t *server)
{
    if (vec_init(&server->clients, sizeof(client_t), (dtor_t) client_teardown,
            NULL)) {
        LOG_ERROR("Failed to initialize clients vector");
        return 1;
    }
    if (server_socket_init(server) < 0) {
        LOG_ERROR("Failed to initialize server socket");
        return 1;
    }
    if (str_init(&server->command.read_buf, "") != BUF_OK) {
        LOG_ERROR("Failed to initialize command read buffer");
        return 1;
    }
    if (str_init(&server->command.write_buf, "") != BUF_OK) {
        LOG_ERROR("Failed to initialize command write buffer");
        return 1;
    }
    return 0;
}

int server(server_t *server, const char *port_str)
{
    if (server_init(server) < 0)
        return 1;
    server->port = get_port(port_str);
    if (server->port < 0)
        return 1;
    if (server_listen(server, server->port, MAX_CLIENTS) < 0) {
        LOG_ERROR("Failed to listen on port %d", server->port);
        return 1;
    }
    server_run(server);
    LOG_INFO("Server shutting down");
    return 0;
}
