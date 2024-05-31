/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"
#include "trantor/string_utils.h"
#include "trantor/map_fn.h"

void player_error(pcmd_args_t *args)
{
    SAY_KO(&args->player->response_buffer);
}

static void immediate_ppo(pcmd_args_t *args)
{
    talkf(args->log, "ppo %d %d %d %d\n", args->player->n,
        args->player->coord[0], args->player->coord[1],
        args->player->direction + 1);
}

void player_forward(pcmd_args_t *args)
{
    SAY_OK(&args->player->response_buffer);
    player_move(args->player, args->map, args->player->direction);
    if (args->spam_gui)
        immediate_ppo(args);
}

void player_right(pcmd_args_t *args)
{
    SAY_OK(&args->player->response_buffer);
    args->player->direction = (args->player->direction + 1) % 4;
    if (args->spam_gui)
        immediate_ppo(args);
}

void player_left(pcmd_args_t *args)
{
    SAY_OK(&args->player->response_buffer);
    args->player->direction = (args->player->direction + 3) % 4;
    if (args->spam_gui)
        immediate_ppo(args);
}
