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
#include "trantor/map.h"

void init_map(len_t width, len_t height, map_t *map);
void add_ressources(map_t *map);
void free_map(map_t *map);
void player_move(player_t *player, map_t *map, direction_t direction);
void get_tile_line(map_t *map, ray_t ray, len_t len, tile_t **tiles);
tile_t *unbounded_tile_get(map_t *map, int x, int y);
void add_direction(unbounded_coord_t *coord, direction_t direction);
unsigned int get_receiving_square(
    map_t *map, direction_t rdir, coord_t emiter, coord_t receiver);
