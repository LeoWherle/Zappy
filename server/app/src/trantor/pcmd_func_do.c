/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"
#include "trantor/map.h"
#include "serrorh.h"

#include <stdlib.h>

// not implemented
static void warn_player_broadcast(void)
{
}

// CHANGE WITH CALCULATED TILE AND VECTOR FOREACH
void player_broadcast(pcmd_args_t *args)
{
    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        if (vec_at(args->players, i) == args->player)
            continue;
        warn_player_broadcast();
    }
}

void player_fork(pcmd_args_t *args)
{
    player_t *egg = NULL;

    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    egg = malloc(sizeof(player_t));
    init_egg(egg, args->player->team, args->player->x, args->player->y);
    if (vec_push(args->players, egg) != BUF_OK)
        LOG_ERROR("Error while pushing egg to players");
}

// not implemented
static void warn_player_eject(void)
{
}

static bool player_eject_step(pcmd_args_t *args, unsigned int *i)
{
    player_t *tmp;

    if (vec_at(args->players, *i) == args->player)
        return false;
    tmp = vec_at(args->players, *i);
    if (tmp->x != args->player->x || tmp->y == args->player->y)
        return false;
    if (!tmp->is_egg) {
        player_move(tmp, args->map, args->player->direction);
        warn_player_eject();
    } else if (vec_delete_at(args->players, *i) == BUF_OK)
        (*i)--;
    return true;
}

void player_eject(pcmd_args_t *args)
{
    bool has_ejected = false;

    for (unsigned int i = 0; i < args->players->nmemb; i++)
        has_ejected = (has_ejected || player_eject_step(args, &i));
    if (has_ejected && !SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    else if (!has_ejected && !SAY_KO(args->player->response_buffer))
        LOG_ERROR("Error while sending KO to player");
}

void player_set(pcmd_args_t *args)
{
    item_t i;

    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
    i = take_rand_item(&(args->player->inventory));
    ADD_ITEM(*GET_TILE(args->map, args->player->x, args->player->y), i);
}

// not implemented
void player_incantation(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}
