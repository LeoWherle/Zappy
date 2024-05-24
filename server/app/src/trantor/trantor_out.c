/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/map_fn.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
#include "vector.h"

#include <stdlib.h>
#include <time.h>


void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->players);
    destroy_params(&trantor->params);
}

player_t *hatch_team_egg(trantor_t *trantor, const char *team_name)
{
    player_t *temp;
    team_t team;
    int idx = get_team_index(&trantor->params, team_name);

    if (idx == -1)
        return NULL;
    team = (team_t) idx;
    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        temp = vec_at(trantor->players, i);
        if (!temp->is_egg || temp->team != team)
            continue;
        hatch_egg(temp);
        talkf(trantor->log, "pnw %d %d %d %d %d %s\n",
            temp->n, temp->coord[0], temp->coord[1], temp->direction,
            temp->elevation, team_name);
        return temp;
    }
    return NULL;
}

unsigned int count_team_egg(trantor_t *trantor, const char *team_name)
{
    player_t *temp;
    team_t team;
    unsigned int count = 0;
    int idx = get_team_index(&trantor->params, team_name);

    if (idx == -1)
        return 0;
    team = (team_t) idx;
    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        temp = vec_at(trantor->players, i);
        if (!temp->is_egg || temp->team != team)
            continue;
        count++;
    }
    return count;
}

string_t *get_player_buffer(player_t *player)
{
    return player->response_buffer;
}

string_t *get_gui_buffer(trantor_t *trantor)
{
    return trantor->log;
}
