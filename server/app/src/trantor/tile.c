/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** tile source file
*/

#include "trantor/tile.h"

#include <stdlib.h>

const float DENSITIES[7] = {
    0.5f, 0.3f, 0.15f, 0.1f, 0.1f, 0.08f, 0.05f
};

const tile_t INVOCATION_REQUIREMENTS[7] = {
    {{0, 1, 0, 0, 0, 0, 0}},
    {{0, 1, 1, 1, 0, 0, 0}},
    {{0, 2, 0, 1, 0, 2, 0}},
    {{0, 1, 1, 2, 0, 1, 0}},
    {{0, 1, 2, 1, 3, 0, 0}},
    {{0, 1, 2, 3, 0, 1, 0}},
    {{0, 2, 2, 2, 2, 2, 1}}
};

void get_item_count(len_t width, len_t height, tile_t *quants)
{
    len_t total = width * height;

    for (unsigned int i = 0; i < 7; i++) {
        quants->items[i] = (quant_t) (total * DENSITIES[i]);
    }
}

quant_t get_total_items(tile_t *tile)
{
    quant_t total = 0;

    for (unsigned int i = 0; i < 7; i++) {
        total += tile->items[i];
    }
    return total;
}

item_t rand_item(tile_t *items_left, len_t tiles_left)
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

static bool tile_contains_tile(const tile_t *first, const tile_t *second)
{
    for (unsigned int i = 0; i < 7; i++) {
        if (first->items[i] < second->items[i])
            return false;
    }
    return true;
}

bool tile_can_invocate(tile_t *tile, unsigned int level)
{
    return tile_contains_tile(tile, &INVOCATION_REQUIREMENTS[level - 1]);
}

void take_tile_from_tile(tile_t *container, const tile_t *list)
{
    for (unsigned int i = 0; i < 7; i++) {
        container->items[i] -= list->items[i];
    }
}
