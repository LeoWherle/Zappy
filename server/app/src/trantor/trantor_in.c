/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/string_utils.h"
#include "trantor/map_fn.h"
#include "serrorh.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>


void init_trantor(trantor_t *trantor, trantor_params_t *params)
{
    srand(time(NULL));
    trantor->params = *params;
    init_map(params->width, params->height, &trantor->map);
    trantor->players = vec_new(sizeof(player_t), destroy_player, NULL);
    trantor->log = str_new();
}

void feed_player_line(
    player_t *player, const char *line)
{
    talk(player->response_buffer, line);
}

void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
    execute_gcmd(trantor, line);
}

void remove_player(trantor_t *trantor, player_t *player)
{
    player_t *other;
    int idx = -1;

    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        other = vec_at(trantor->players, i);
        if (other == player)
            idx = i;
        if (other->incantator == player)
            other->incantator = NULL;
    }
    if (vec_remove(trantor->players, idx) != BUF_OK)
        LOG_ERROR("Failed to remove player from vector");
}
