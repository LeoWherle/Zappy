/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"
#include "serrorh.h"

void player_error(pcmd_args_t *args)
{
    if (!SAY_KO(args->player->response_buffer))
        LOG_ERROR("Error while sending KO to player");
}

void player_forward(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    player_move(args->player, args->map, args->player->direction);
}

void player_right(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    args->player->direction = (args->player->direction + 1) % 4;
}

void player_left(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    args->player->direction = (args->player->direction + 3) % 4;
}
