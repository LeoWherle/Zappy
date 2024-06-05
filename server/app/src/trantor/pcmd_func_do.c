/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/direction.h"
#include "trantor/pcmd_args.h"
#include "trantor/map_fn.h"
#include "serrorh.h"
#include "trantor/tile.h"
#include "trantor/string_utils.h"


void player_broadcast(pcmd_args_t *args)
{
    player_t *p;
    unsigned int sq = 0;

    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        p = (player_t *) vec_at(args->players, i);
        if (p == args->player || p->is_egg || p->is_dead)
            continue;
        sq = get_receiving_square(args->map, p->direction,
            args->player->coord, p->coord);
        talkf(&p->response_buffer, "message %d, %s", sq, args->broadcast_msg);
    }
    SAY_OK(&args->player->response_buffer);
    talkf(args->log, "pbc %d %s\n", args->player->n, args->broadcast_msg);
}

void player_fork(pcmd_args_t *args)
{
    player_t egg = {0};

    SAY_OK(&args->player->response_buffer);
    init_egg(&egg, args->player->team, args->player->coord);
    talkf(args->log, "enw %d %d %d %d\n", egg.n, args->player->n,
        egg.coord[0], egg.coord[1]);
    if (args->spam_gui)
        talkf(args->log, "eht %d\n", args->player->n);
    else
        talkf(args->log, "pfk %d\n", args->player->n);
    if (vec_push(args->players, &egg) != BUF_OK)
        LOG_ERROR("Error while pushing egg to players");
}

static void warn_player_eject(
    player_t *player, direction_t from, string_t *log)
{
    direction_t relative = (4 + (from - player->direction)) % 4;

    if (player->is_egg) {
        talkf(log, "edi %d\n", player->n);
        return;
    }
    talkf(&player->response_buffer, "eject: %d\n", relative);
}

static bool player_eject_step(pcmd_args_t *args, unsigned int *i)
{
    player_t *tmp;

    if (vec_at(args->players, *i) == args->player)
        return false;
    tmp = vec_at(args->players, *i);
    if (COORD_EQ(tmp->coord, args->player->coord))
        return false;
    warn_player_eject(tmp, (args->player->direction + 2) % 4, args->log);
    if (!tmp->is_egg) {
        player_move(tmp, args->map, args->player->direction);
    } else if (vec_delete_at(args->players, *i) == BUF_OK)
        (*i)--;
    return true;
}

void player_eject(pcmd_args_t *args)
{
    bool has_ejected = false;

    for (unsigned int i = 0; i < args->players->nmemb; i++)
        has_ejected = (has_ejected || player_eject_step(args, &i));
    if (has_ejected) {
        SAY_OK(&args->player->response_buffer);
        talkf(args->log, "pex %d\n", args->player->n);
    } else
        SAY_KO(&args->player->response_buffer);
}

void player_set(pcmd_args_t *args)
{
    item_t i;
    tile_t *t;

    t = CGET_TILE(args->map, args->player->coord);
    if (!HAS_ITEM(args->player->inventory, args->item)) {
        SAY_KO(&args->player->response_buffer);
        return;
    }
    i = TAKE_ITEM(args->player->inventory, args->item);
    ADD_ITEM(*t, i);
    SAY_OK(&args->player->response_buffer);
    talkf(args->log, "pdr %d %d\n", args->player->n, args->item - 1);
}
