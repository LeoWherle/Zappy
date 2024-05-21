/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map source file
*/

#include "trantor/map.h"

#include <stdlib.h>

const char *ITEM_NAMES[7] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

const float DENSITIES[7] = {
    0.5f, 0.3f, 0.15f, 0.1f, 0.1f, 0.08f, 0.05f
};

const int DIRECTIONS[4][2] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

void init_map(len_t width, len_t height, map_t *map)
{
    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t) * width * height);
    for (len_t i = 0; i < width * height; i++) {
        for (int j = 0; j < 7; j++) {
            map->tiles[i].items[j] = 0;
        }
    }
}

void free_map(map_t *map)
{
    free(map->tiles);
}

void player_move(player_t *player, map_t *map, direction_t direction)
{
    int new_x = ((int)player->x) + DIRECTIONS[direction][0];
    int new_y = ((int)player->y) + DIRECTIONS[direction][1];

    if (new_x < 0)
        new_x = ((int) map->width) - 1;
    if (new_y < 0)
        new_y = ((int) map->height) - 1;
    if (new_x >= ((int) map->width))
        new_x = 0;
    if (new_y >= ((int) map->height))
        new_y = 0;
    player->x = (len_t) new_x;
    player->y = (len_t) new_y;
}
