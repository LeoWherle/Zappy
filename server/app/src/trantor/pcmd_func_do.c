/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/direction.h"
#include "trantor/pcmd_args.h"
#include "trantor/map.h"
#include "serrorh.h"

#include <stdio.h>
#include <stdlib.h>


static void warn_player_broadcast(
    player_t *player, const char *m, unsigned int sq)
{
    char *msg = NULL;
    size_t len = 0;

    len = snprintf(NULL, 0, "message %d, %s", sq, m);
    msg = malloc(sizeof(char) * (len + 1));
    sprintf(msg, "message %d, %s", sq, m);
    if (!SAY(player->response_buffer, msg))
        LOG_ERROR("Error while pushing broadcast message to player");
}

void player_broadcast(pcmd_args_t *args)
{
    player_t *p;
    unsigned int sq = 0;

    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        p = vec_at(args->players, i);
        if (p == args->player)
            continue;
        sq = get_receiving_square(args->map, p->direction,
            (coord_t){args->player->x, args->player->y},
            (coord_t){p->x, p->y});
        warn_player_broadcast(p, args->player->pcmd_exec.arg, sq);
    }
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
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

static void warn_player_eject(player_t *player, direction_t from)
{
    char *msg = NULL;
    size_t len = 0;
    direction_t relative = (4 + (from - player->direction)) % 4;

    len = snprintf(NULL, 0, "eject: %d", relative);
    msg = malloc(sizeof(char) * (len + 1));
    sprintf(msg, "eject: %d", relative);
    if (!SAY(player->response_buffer, msg))
        LOG_ERROR("Error while pushing eject message to player");
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
        warn_player_eject(tmp, (args->player->direction + 2) % 4);
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
    tile_t *t;

    t = GET_TILE(args->map, args->player->x, args->player->y);
    if (!HAS_ITEM(args->player->inventory, args->item)) {
        if (!SAY_KO(args->player->response_buffer))
            LOG_ERROR("Error while sending KO to player");
        return;
    }
    i = TAKE_ITEM(args->player->inventory, args->item);
    ADD_ITEM(*t, i);
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}

void player_incantation(pcmd_args_t *args)
{
    if (!SAY_OK(args->player->response_buffer))
        LOG_ERROR("Error while sending OK to player");
}
