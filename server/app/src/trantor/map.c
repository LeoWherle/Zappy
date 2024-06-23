/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map source file
*/

#include "trantor/map.h"
#include "trantor/config.h"

#include <stdlib.h>

// calculate the diff between result of get_item_count and what's on the map
static void get_missing_items(map_t *map, tile_t *missing)
{
    tile_t item_tile = {0};

    get_item_count(map->width, map->height, &item_tile);
    for (len_t i = 0; i < map->width * map->height; i++) {
        for (unsigned int j = 0; j < ITEM_COUNT - 1; j++) {
            missing->items[j] += map->tiles[i].items[j];
        }
    }
    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        if (missing->items[i] <= item_tile.items[i])
            missing->items[i] = item_tile.items[i] - missing->items[i];
        else
            missing->items[i] = 0;
    }
}

static void add_all_ressources(map_t *map, tile_t *item_tile)
{
    unsigned int idx = 0;

    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        for (quant_t j = 0; j < item_tile->items[i]; j++) {
            idx = rand() % (map->width * map->height);
            ADD_ITEM(map->tiles[idx], i + 1);
        }
    }
}

void init_map(len_t width, len_t height, map_t *map)
{
    tile_t item_tile = {0};

    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t) * width * height);
    map->since_refill = 0.0;
    get_item_count(width, height, &item_tile);
    for (len_t i = 0; i < width * height; i++) {
        map->tiles[i] = (tile_t){0};
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
