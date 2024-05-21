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

static void get_item_count(len_t width, len_t height, tile_t *quants)
{
    len_t total = width * height;

    for (unsigned int i = 0; i < 7; i++) {
        quants->items[i] = (quant_t) (total * DENSITIES[i]);
    }
}

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

static quant_t get_total_items(tile_t *tile)
{
    quant_t total = 0;

    for (unsigned int i = 0; i < 7; i++) {
        total += tile->items[i];
    }
    return total;
}

static item_t rand_item(tile_t *items_left, len_t tiles_left)
{
    quant_t total = get_total_items(items_left);
    double item_prob = (double) total / (double) tiles_left;
    double rand_prob = (double) rand() / (double) RAND_MAX;

    if (rand_prob > item_prob)
        return NONE_ITEM;
    for (unsigned int i = 0; i < 7; i++) {
        if (rand_prob < (double) items_left->items[i] / (double) total)
            return i + 1;
        rand_prob -= (double) items_left->items[i] / (double) total;
    }
    return NONE_ITEM;
}

static void add_item(len_t i, tile_t *item_tile, map_t *map)
{
    item_t tmp;

    for (unsigned int j = 0; j < 7; j++) {
        tmp = rand_item(item_tile, map->width * map->height);
        if (tmp == NONE_ITEM)
            continue;
        ADD_ITEM(map->tiles[i], tmp);
    }
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
        add_item(i, &item_tile, map);
    }
}

static void add_ressources(map_t *map)
{
    tile_t item_tile = {0};

    get_missing_items(map, &item_tile);
    for (len_t i = 0; i < map->width * map->height; i++) {
        add_item(i, &item_tile, map);
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
