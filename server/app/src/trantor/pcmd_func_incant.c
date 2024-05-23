/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "trantor/pcmd_args.h"
#include "trantor/map.h"
#include "serrorh.h"
#include "trantor/tile.h"

#include <stdio.h>
#include <stdlib.h>


const unsigned int NPLAYER_ELEV_REQ[7] = {1, 2, 2, 4, 4, 6, 6};
const char ELEV_MSG[] = "Elevation underway\nCurrent level: %d";

static unsigned int count_players_on_tile(
    vector_t *players, player_t *invocator)
{
    unsigned int count = 0;
    player_t *p = NULL;

    for (unsigned int i = 0; i < players->nmemb; i++) {
        p = vec_at(players, i);
        if (p->x == invocator->x && p->y == invocator->y
            && p->elevation == invocator->elevation)
            count++;
    }
    return count;
}

bool can_invocate(vector_t *players, player_t *invocator, map_t *map)
{
    bool enough_players = count_players_on_tile(players, invocator)
        >= NPLAYER_ELEV_REQ[invocator->elevation - 1];
    bool stones_presents = tile_can_invocate(
        GET_TILE(map, invocator->x, invocator->y),
        invocator->elevation);

    return enough_players && stones_presents;
}

static void elevate_players(pcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;
    player_t *p = NULL;

    len = snprintf(NULL, 0, ELEV_MSG, args->player->elevation + 1);
    msg = malloc(sizeof(char) * (len + 1));
    sprintf(msg, ELEV_MSG, args->player->elevation + 1);
    for (unsigned int i = 0; i < args->players->nmemb; i++) {
        p = vec_at(args->players, i);
        if (!(p->x == args->player->x && p->y == args->player->y
            && p->elevation == args->player->elevation))
            continue;
        p->elevation++;
        if (!SAY(p->response_buffer, msg))
            LOG_ERROR("Error while pushing elevation message to player");
        p->incantator = NULL;
    }
}

void player_incantation(pcmd_args_t *args)
{
    if (!can_invocate(args->players, args->player, args->map)) {
        if (!SAY_KO(args->player->response_buffer))
            LOG_ERROR("Error while sending KO to player");
        return;
    }
    tile_invocate(GET_TILE(args->map, args->player->x, args->player->y),
        args->player->elevation);
    elevate_players(args);
}
