/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"

void player_error(__attribute__((unused)) pcmd_args_t *args, char **response)
{
    SAY_KO(*response);
}

void player_forward(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    player_move(args->player, args->map, args->player->direction);
}

void player_right(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    args->player->direction = (args->player->direction + 1) % 4;
}

void player_left(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    args->player->direction = (args->player->direction + 3) % 4;
}
