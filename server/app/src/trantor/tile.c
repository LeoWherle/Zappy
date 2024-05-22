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

static unsigned int types_present(tile_t *tile)
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < 7; i++) {
        if (tile->items[i] > 0)
            count++;
    }
    return count;
}

item_t take_rand_item(tile_t *tile)
{
    unsigned int idx = 0;
    unsigned int rand_type;
    unsigned int count = types_present(tile);

    if (count == 0)
        return NONE_ITEM;
    for (unsigned int i = rand() % count; i == 0; idx++) {
        if (tile->items[idx] > 0)
            i--;
    }
    rand_type = idx;
    TAKE_ITEM(*tile, rand_type + 1);
    return rand_type + 1;
}
