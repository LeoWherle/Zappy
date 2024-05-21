/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"
#include "serrorh.h"

// CHANGE WITH CALCULATED TILE AND VECTOR FOREACH
void player_broadcast(pcmd_args_t *args)
{
    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        if (vec_at(args->players, i) == args->player)
            continue;
        if (vec_push(((player_t *)vec_at(args->players, i))->response_buffer,
            args->broadcast_msg) != BUF_OK)
            LOG_ERROR("Error while sending broadcast to player");
    }
}

// not implemented
void player_fork(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}

// not implemented
void player_eject(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}

// not implemented
void player_set(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}

// not implemented
void player_incantation(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}
