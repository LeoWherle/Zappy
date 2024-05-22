/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
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
}

void feed_player_line(
    player_t *player, const char *line)
{
    if (vec_push(player->pcmd_buffer, strdup(line)) != BUF_OK)
        LOG_ERROR("Error while pushing line to player buffer");
}

// not implemented
void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
}
