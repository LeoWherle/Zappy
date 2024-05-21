/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** main
*/

#include "common.h"
#include "serrorh.h"
#include "server.h"
#include <stdio.h>
#include <unistd.h>

static void server_teardown(server_t *server)
{
    if (server == NULL) {
        return;
    }
    vec_reset(&server->clients);
    vec_reset(&server->command.read_buf);
    vec_reset(&server->command.write_buf);
    close(server->listen_sd);
}

int main(int ac, char *av[])
{
    server_t server_data = {0};
    int ret = 0;

    if (ac != 2) {
        printf("Usage: %s <port>\n", av[0]);
        return (84);
    }
    LOG_TRACE("Starting server");
    init_logging("server.env");
    ret = server(&server_data, av[1]) != 0;
    ret = ret ? 84 : 0;
    server_teardown(&server_data);
    return ret;
}
