/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** tcp_server
*/

#include "serrorh.h"
#include "server.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @brief intialize a TCP server socket as AF_INET, SOCK_STREAM, IPPROTO_TCP.
 * Sets the listen_sd field of the server to the socket descriptor
 * @param server the server to initialize the socket for
 * @return 0 on success, -1 on failure
 */
int server_socket_init(server_t *server)
{
    struct linger on = {1, 0};
    size_t linger_len = sizeof(struct linger);
    int listen_sd = 0;
    int ret = 0;

    if (server == NULL)
        return -1;
    listen_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sd >= 0) {
        ret = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, &on, linger_len);
        if (ret >= 0) {
            server->listen_sd = listen_sd;
            return 0;
        }
        perror("setsockopt() failed");
        close(listen_sd);
    }
    perror("socket() failed");
    return -1;
}

int server_listen(server_t *server, uint16_t port, int max_clients)
{
    socklen_t size = sizeof(server->addr);

    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->addr.sin_port = htons(port);
    if (bind(server->listen_sd, (struct sockaddr *) &server->addr, size) < 0) {
        return -1;
    }
    if (listen(server->listen_sd, max_clients) < 0) {
        return -1;
    }
    LOG_INFO("Listening on a address: %s:%d", inet_ntoa(server->addr.sin_addr),
        ntohs(server->addr.sin_port));
    return 0;
}

server_t *server_create(void)
{
    server_t *server = NULL;

    server = calloc(1, sizeof(*server));
    if (server != NULL) {
        if (server_socket_init(server) < 0) {
            free(server);
            return NULL;
        }
    }
    return server;
}

void server_destroy(server_t *server)
{
    if (server != NULL) {
        close(server->listen_sd);
        free(server);
    }
}
