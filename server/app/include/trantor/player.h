/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player header
*/

#pragma once

#include "trantor/map.h"

#define PLAYER_IS_AT(pl, x, y) (pl.x == x && pl.y == y)

typedef struct player_s {
    bool is_egg;
    team_t team;
    len_t x;
    len_t y;
    direction_t direction;
    tile_t inventory;
    elevation_t elevation;
    vector_t *pcmd_buffer; // stores received commands
    vector_t *response_buffer; // stores responses
    bool busy;
} player_t;

void init_player(player_t *player, team_t team, len_t x, len_t y);
void init_egg(player_t *player, team_t team, len_t x, len_t y);
void hatch_egg(player_t *player);
void destroy_player(player_t *player);
void player_move(player_t *player, map_t *map, direction_t direction);
