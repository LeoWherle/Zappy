/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** main
*/

#include "serrorh.h"
#include "server.h"
#include "trantor/params.h"
#include <stdio.h>
#include <sys/cdefs.h>
#include <unistd.h>

const char USAGE[] = (
    "USAGE: ./zappy_server -p port -x width -y height "
    "-n name1 name2 ... -c clientsNb -f freq\n"
    "option description                                       default values\n"
    "    -p port port number                                  (4242)\n"
    "    -x width width of the world                          (10)\n"
    "    -y height height of the world                        (10)\n"
    "    -n name1 name2 .. . name of the team                 ----\n"
    "    -c clientsNb number of starting eggs per team        (10)\n"
    "    -f freq reciprocal of time unit for actions          (2)\n"
    "    -s seed for reproductible runs                       (0 for rdm)\n"
    "    --spam-gui spam the gui with all the commands        (no spam)\n"
    "    --paused start the game paused                       (no pause)\n");

static void server_teardown(server_t *server)
{
    if (server == NULL) {
        return;
    }
    sleep(5);
    vec_reset(&server->clients);
    str_reset(&server->command.read_buf);
    str_reset(&server->command.write_buf);
    close(server->listen_sd);
    free_trantor(&server->trantor);
}

// This is a trick to call the constructor and destructor functions from
// static libraries
void prog_constructors(void)
{
    void (*f)(void) = pre_load_env;
    void (*g)(void) = post_load_env;

    f();
    g();
}

int main(int ac, char *av[])
{
    server_t server_data = {0};
    int ret = 0;

    LOG_TRACE("Starting server");
    --ac;
    ++av;
    if (!parse_args(ac, av, &server_data.trantor.params)) {
        destroy_params(&server_data.trantor.params);
        printf("%s", USAGE);
        return 84;
    }
    ret = server(&server_data, server_data.trantor.params.port) != 0;
    ret = ret ? 84 : 0;
    server_teardown(&server_data);
    return ret;
}
