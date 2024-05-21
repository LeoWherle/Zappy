/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player source file
*/

#include "trantor/pcmd.h"

void player_error(pcmd_args_t *args, char **response)
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

void player_look(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_inventory(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_broadcast(pcmd_args_t *args, char **response)
{
    broadcast_buffer_t *buf = (broadcast_buffer_t *) response;

    buf->pos[0] = args->player->x;
    buf->pos[1] = args->player->y;
    buf->msg = args->broadcast_msg;
}

void player_co_num(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_fork(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    // not implemented
}

void player_eject(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_death(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_take(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_set(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_incantation(pcmd_args_t *args, char **response)
{
    // not implemented
}
