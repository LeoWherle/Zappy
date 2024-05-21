/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/pcmd.h"

void init_trantor(trantor_t *trantor, trantor_params_t *params)
{
    trantor->params = *params;
    init_map(params->width, params->height, &trantor->map);
    trantor->players = vec_new(sizeof(player_t), destroy_player, NULL);
    trantor->player_executors = vec_new(sizeof(pcmd_executor_t), NULL, NULL);
}

void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->players);
    vec_delete(trantor->player_executors);
}

player_t *get_team_egg(vector_t *players, team_t team)
{
    player_t *temp;

    for (unsigned int i = 0; i < players->nmemb; i++) {
        temp = vec_at(players, i);
        if (temp->is_egg && temp->team == team)
            return temp;
    }
    return NULL;
}

// not implemented
void player_feed_trantor_line(
    player_t *player, trantor_t *trantor, const char *line)
{
}

// not implemented
void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
}
