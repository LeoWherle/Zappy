/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "sstrings.h"
#include "trantor.h"
#include "trantor/common.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static player_t *hatch_team_egg_step(
    player_t *temp, int *n, team_t team)
{
    if (!temp->is_egg || temp->team != team)
        return NULL;
    if (*n == 0) {
        hatch_egg(temp);
        return temp;
    }
    (*n)--;
    return NULL;
}

player_t *hatch_team_egg(trantor_t *trantor, const char *team_name)
{
    player_t *np = NULL;
    team_t team = (team_t) get_team_index(&trantor->params, team_name);
    int n;

    if (team == (team_t) -1)
        return NULL;
    n = rand() % count_idxteam_egg(trantor, team);
    for (unsigned int i = 0; i < trantor->players.nmemb; i++) {
        np = hatch_team_egg_step(VEC_AT(&trantor->players, i), &n, team);
        if (np)
            break;
    }
    if (!np)
        return NULL;
    talkf(&trantor->log, "ebo %d\n", (int) np->n);
    talkf(&trantor->log, "pnw %d %d %d %d %d %s\n", np->n, np->coord[0],
        np->coord[1], np->direction + 1, np->elevation, team_name);
    return np;
}

unsigned int count_idxteam_egg(trantor_t *trantor, team_t t)
{
    player_t *temp;
    unsigned int count = 0;

    for (unsigned int i = 0; i < trantor->players.nmemb; i++) {
        temp = (player_t *) vec_at(&trantor->players, i);
        if (!temp->is_egg || temp->team != t)
            continue;
        count++;
    }
    return count;
}

unsigned int count_team_egg(trantor_t *trantor, const char *team_name)
{
    int idx = get_team_index(&trantor->params, team_name);

    if (idx == -1)
        return 0;
    return count_idxteam_egg(trantor, (team_t) idx);
}

string_t *get_player_buffer(player_t *player)
{
    return &player->response_buffer;
}

string_t *get_gui_buffer(trantor_t *trantor)
{
    return &trantor->log;
}
