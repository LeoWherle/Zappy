/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"
#include "serrorh.h"

#include <stdlib.h>
#include <stdio.h>

const char *ITEM_NAMES[7] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

// not implemented
void player_look(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}

void player_inventory(pcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 2 + 6;

    for (unsigned int i = 0; i < 7; i++)
        len += snprintf(NULL, 0, "%s %d", ITEM_NAMES[i],
            args->player->inventory.items[i]);
    msg = malloc(sizeof(char) * (len + 1));
    len = sprintf(msg, "[");
    for (unsigned int i = 0; i < 7; i++) {
        len += sprintf(msg + len, "%s %d", ITEM_NAMES[i],
            args->player->inventory.items[i]);
        if (i != 6)
            len += sprintf(msg + len, ", ");
    }
    len += sprintf(msg + len, "]");
    if (vec_push(args->player->response_buffer, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to response buffer");
}

void player_co_num(pcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;

    len = snprintf(NULL, 0, "%d\n", args->cnb);
    msg = malloc(sizeof(char) * (len + 1));
    sprintf(msg, "%d\n", args->cnb);
    if (vec_push(args->player->response_buffer, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to response buffer");
}

void player_take(pcmd_args_t *args)
{
    item_t i;

    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    i = take_rand_item(GET_TILE(args->map, args->player->x, args->player->y));
    if (i == NONE_ITEM)
        return;
    ADD_ITEM(args->player->inventory, i);
}
