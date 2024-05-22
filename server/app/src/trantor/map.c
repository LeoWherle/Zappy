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

const int DIRECTIONS[4][2] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

// calculate the diff between result of get_item_count and what's on the map
static void get_missing_items(map_t *map, tile_t *missing)
{
    tile_t item_tile = {0};

    get_item_count(map->width, map->height, &item_tile);
    for (len_t i = 0; i < map->width * map->height; i++) {
        for (unsigned int j = 0; j < 7; j++) {
            missing->items[j] += map->tiles[i].items[j];
        }
    }
    for (unsigned int i = 0; i < 7; i++) {
        missing->items[i] = item_tile.items[i] - missing->items[i];
    }
}

static void add_item(len_t i, tile_t *item_tile, map_t *map)
{
    item_t tmp;

    for (unsigned int j = 0; j < 7; j++) {
        tmp = rand_item(item_tile, map->width * map->height);
        if (tmp == NONE_ITEM)
            continue;
        ADD_ITEM(map->tiles[i], tmp);
        TAKE_ITEM(*item_tile, tmp);
    }
}

// recursive to ensure all items are added
static void add_all_ressources(map_t *map, tile_t *item_tile)
{
    for (len_t i = 0; i < map->width * map->height; i++) {
        add_item(i, item_tile, map);
    }
    if (get_total_items(item_tile) > 0)
        add_all_ressources(map, item_tile);
}

void init_map(len_t width, len_t height, map_t *map)
{
    tile_t item_tile = {0};

    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t) * width * height);
    get_item_count(width, height, &item_tile);
    for (len_t i = 0; i < width * height; i++) {
        map->tiles[i] = (tile_t) {0};
    }
    add_all_ressources(map, &item_tile);
}

void add_ressources(map_t *map)
{
    tile_t item_tile = {0};

    get_missing_items(map, &item_tile);
    add_all_ressources(map, &item_tile);
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
