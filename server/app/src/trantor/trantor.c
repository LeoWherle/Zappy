/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"

bool parse_args(int ac, char **av, trantor_params_t *params)
{
    // not implemented
    return true;
}

void init_trantor(trantor_t *trantor, trantor_params_t *params)
{
    trantor->params = *params;
    init_map(params->width, params->height, &trantor->map);
    trantor->free_players = vec_new(sizeof(player_t), NULL, destroy_player);
    trantor->player_executors = vec_new(sizeof(pcmd_executor_t), NULL, NULL);
}

void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->free_players);
    vec_delete(trantor->player_executors);
}

player_t *get_team_egg(vector_t *players, const char *team)
{
    for (unsigned int i = 0; i < players->size; i++) {
        player_t *player = vec_get(players, i);

        if (player->is_egg && strcmp(player->team, team) == 0)
            return player;
    }
    return NULL;
}

void player_feed_trantor_line(player_t *player, trantor_t *trantor, const char *line)
{
    // not implemented
}

void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
    // not implemented
}
