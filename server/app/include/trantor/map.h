/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map header
*/

#pragma once

#include "trantor/direction.h"
#include "trantor/tile.h"

typedef struct map_s {
    len_t width;
    len_t height;
    tile_t *tiles;
    double since_refill;
} map_t;

typedef len_t coord_t[2];

typedef int unbounded_coord_t[2];

typedef struct ray_s {
    unbounded_coord_t start;
    direction_t direction;
} ray_t;

#define GET_TILE(map, x, y) (map->tiles + (y * map->width + x))
#define CGET_TILE(map, c) (map->tiles + (c[1] * map->width + c[0]))

#define COORD_EQ(a, b) (a[0] == b[0] && a[1] == b[1])
