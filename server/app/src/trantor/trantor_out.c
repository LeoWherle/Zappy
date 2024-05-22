/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"

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
        return temp;
    }
    return NULL;
}

// not implemented
void trantor_time_pass(trantor_t *trantor)
{
}

vector_t *get_player_buffer(player_t *player)
{
    return player->response_buffer;
}

vector_t *get_gui_buffer(trantor_t *trantor)
{
    return trantor->log;
}
