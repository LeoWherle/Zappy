/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/config.h"
#include "trantor/pcmd_args.h"
#include "trantor/map.h"
#include "trantor/tile.h"
#include "trantor/string_utils.h"

#include <stdio.h>
#include <stdlib.h>

const char ELEV_MSG[] = "Elevation underway\nCurrent level: %d\n";

static unsigned int count_players_on_tile(
    vector_t *players, player_t *invocator)
{
    unsigned int count = 0;
    player_t *p = NULL;

    for (unsigned int i = 0; i < players->nmemb; i++) {
        p = vec_at(players, i);
        if (p->is_egg || p->is_dead)
            continue;
        if (COORD_EQ(p->coord, invocator->coord)
            && p->elevation == invocator->elevation)
            count++;
    }
    return count;
}

bool can_invocate(vector_t *players, player_t *invocator, map_t *map)
{
    bool enough_players = count_players_on_tile(players, invocator)
        >= get_elev_players(invocator->elevation);
    bool stones_presents = tile_can_invocate(
        CGET_TILE(map, invocator->coord), invocator->elevation);

    return enough_players && stones_presents;
}

static void unfreeze_players(pcmd_args_t *args)
{
    player_t *p = NULL;

    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        p = vec_at(args->players, i);
        if (!COORD_EQ(p->coord, args->player->coord)
            || p->elevation != args->player->elevation)
            continue;
        p->incantator = NULL;
    }
}

static void elevate_players(pcmd_args_t *args)
{
    char *msg = NULL;
    player_t *p = NULL;

    msg = aprintf(ELEV_MSG, args->player->elevation + 1);
    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        p = vec_at(args->players, i);
        if (p->is_egg || p->is_dead || p == args->player
            || !COORD_EQ(p->coord, args->player->coord)
            || p->elevation != args->player->elevation)
            continue;
        p->elevation++;
        talk(&p->response_buffer, msg);
    }
    args->player->elevation++;
    talk(&args->player->response_buffer, msg);
    free(msg);
}

void player_incantation(pcmd_args_t *args)
{
    unfreeze_players(args);
    if (!can_invocate(args->players, args->player, args->map)) {
        SAY_KO(&args->player->response_buffer);
        talkf(args->log, "pie %d %d 0\n", args->player->coord[0],
            args->player->coord[1]);
        return;
    }
    tile_invocate(CGET_TILE(args->map, args->player->coord),
        args->player->elevation);
    elevate_players(args);
    talkf(args->log, "pie %d %d 1\n", args->player->coord[0],
        args->player->coord[1]);
}
