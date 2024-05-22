/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/pcmd.h"

#include <stdlib.h>
#include <time.h>


void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->players);
    destroy_params(&trantor->params);
}

player_t *hatch_team_egg(vector_t *players, team_t team)
{
    player_t *temp;

    for (unsigned int i = 0; i < players->nmemb; i++) {
        temp = vec_at(players, i);
        if (temp->is_egg && temp->team == team) {
            hatch_egg(temp);
            return temp;
        }
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
