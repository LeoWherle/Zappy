/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** give
*/

#include "commands/give.h"
#include "serrorh.h"
#include "sstrings.h"
#include <string.h>
#include <strings.h>
#include <sys/types.h>

give_cmd_t targets[] = {
    {"all", 'a', give_all},
    {"random", 'r', give_random},
    {"player", 'p', give_player},
    {"team", 't', give_team},
};

void give_all(server_t *serv, serv_context_t *contx, vector_t *args)
{
}

void give_random(server_t *serv, serv_context_t *contx, vector_t *args)
{
}

void give_player(server_t *serv, serv_context_t *contx, vector_t *args)
{
}

void give_team(server_t *serv, serv_context_t *contx, vector_t *args)
{
}

void command_give(server_t *server, serv_context_t *context, vector_t *args)
{
    const char *target = NULL;

    if (args->nmemb != 2)
        LOG_ERROR("Expected: give all|random|player|team ...");
    target = *(const char **) vec_at(args, 1);
    for (size_t i = 0; i < sizeof(targets) / sizeof(*targets); i++) {
        if (strcasecmp(target, targets[i].target)) {
            if (vec_erase(args, 0, 2))
                return (void) LOG_ERROR("Failed to process arguments");
            return targets[i].callback(server, context, args);
        }
        if (strlen(target) == 2 && target[0] == '@'
            && target[1] == targets[i].target_short) {
            if (vec_erase(args, 0, 2))
                return (void) LOG_ERROR("Failed to process arguments");
            return targets[i].callback(server, context, args);
        }
    }
    return (void) LOG_ERROR("Invalid target: %s", target);
}
