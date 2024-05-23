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
    SAY_KO(args->player->response_buffer);
}

void player_forward(pcmd_args_t *args)
{
    SAY_OK(args->player->response_buffer);
    player_move(args->player, args->map, args->player->direction);
}

void player_right(pcmd_args_t *args)
{
    SAY_OK(args->player->response_buffer);
    args->player->direction = (args->player->direction + 1) % 4;
}

void player_left(pcmd_args_t *args)
{
    SAY_OK(args->player->response_buffer);
    args->player->direction = (args->player->direction + 3) % 4;
}
