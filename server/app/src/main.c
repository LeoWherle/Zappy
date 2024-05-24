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

const char USAGE[] = (
    "USAGE: ./zappy_server -p port -x width -y height "
    "-n name1 name2 ... -c clientsNb -f freq\n"
    "option description\n"
    "    -p port port number\n"
    "    -x width width of the world\n"
    "    -y height height of the world\n"
    "    -n name1 name2 .. . name of the team\n"
    "    -c clientsNb number of authorized clients per team\n"
    "    -f freq reciprocal of time unit for execution of actions"
);

static void server_teardown(server_t *server)
{
    if (server == NULL) {
        return;
    }
    vec_reset(&server->clients);
    str_reset(&server->command.read_buf);
    str_reset(&server->command.write_buf);
    close(server->listen_sd);
    free_trantor(&server->trantor);
}

int main(int ac, char *av[])
{
    server_t server_data = {0};
    int ret = 0;

    if (!parse_args(ac, av, &server_data.trantor.params)) {
        printf("%s", USAGE);
        return (84);
    }
    LOG_TRACE("Starting server");
    init_logging("server.env");
    ret = server(&server_data, server_data.trantor.params.port) != 0;
    ret = ret ? 84 : 0;
    server_teardown(&server_data);
    return ret;
}
