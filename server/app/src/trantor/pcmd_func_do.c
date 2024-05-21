/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd.h"

void player_broadcast(pcmd_args_t *args, char **response)
{
    broadcast_buffer_t *buf = (broadcast_buffer_t *) response;

    buf->pos[0] = args->player->x;
    buf->pos[1] = args->player->y;
    buf->msg = args->broadcast_msg;
}

// not implemented
void player_fork(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
}

// not implemented
void player_eject(pcmd_args_t *args, char **response)
{
}

// not implemented
void player_set(pcmd_args_t *args, char **response)
{
}

// not implemented
void player_incantation(pcmd_args_t *args, char **response)
{
}
