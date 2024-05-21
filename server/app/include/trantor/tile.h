/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** tile header
*/

#pragma once

#include "trantor/common.h"

#define GET_ITEM(tl, tp) (tl.items[tp - 1])
#define SET_ITEM(tl, tp, val) (tl.items[tp - 1] = val)
#define HAS_ITEM(tl, tp) (GET_ITEM(tl, tp) > 0)
#define TAKE_ITEM(tl, tp) (GET_ITEM(tl, tp)--)
#define ADD_ITEM(tl, tp) (GET_ITEM(tl, tp)++)

typedef enum item_e {
    NONE_ITEM = 0,
    FOOD_ITEM = 1,
    LINEMATE_ITEM = 2,
    DERAUMERE_ITEM = 3,
    SIBUR_ITEM = 4,
    MENDIANE_ITEM = 5,
    PHIRAS_ITEM = 6,
    THYSTAME_ITEM = 7
} item_t;

typedef struct tile_s {
    quant_t items[7];
} tile_t;
