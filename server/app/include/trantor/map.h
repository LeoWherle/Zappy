/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map header
*/

#pragma once

#include "trantor/direction.h"
#include "trantor/tile.h"
#include "trantor/player.h"

typedef struct map_s {
    len_t width;
    len_t height;
    tile_t *tiles;
} map_t;

#define GET_TILE(map, x, y) (map->tiles + (y * map->width + x))

void init_map(len_t width, len_t height, map_t *map);
void free_map(map_t *map);
void player_move(player_t *player, map_t *map, direction_t direction);
