/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor header
*/

#pragma once

#include "trantor/player.h"
#include "trantor/map.h"
#include "trantor/params.h"

typedef struct trantor_s {
    trantor_params_t params;
    map_t map;
    vector_t *players;
    vector_t *log;
} trantor_t;

void init_trantor(trantor_t *trantor, trantor_params_t *params);
void free_trantor(trantor_t *trantor);
player_t *get_team_egg(vector_t *players, team_t team);
void player_feed_trantor_line(
    player_t *player, trantor_t *trantor, const char *line);
void gui_feed_trantor_line(trantor_t *trantor, const char *line);
