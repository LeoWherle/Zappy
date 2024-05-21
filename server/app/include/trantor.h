/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor header
*/

#pragma once

// in case we want to change
typedef unsigned int quant_t;
typedef unsigned int len_t;
typedef unsigned int team_t;

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

const char *ITEM_NAMES[7] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

typedef struct tile_s {
    quant_t items[7];
} tile_t;

#define GET_ITEM(tl, tp) (tl.items[tp - 1])
#define SET_ITEM(tl, tp, val) (tl.items[tp - 1] = val)

#define HAS_ITEM(tl, tp) (GET_ITEM(tl, tp) > 0)

#define TAKE_ITEM(tl, tp) (GET_ITEM(tl, tp)--)
#define ADD_ITEM(tl, tp) (GET_ITEM(tl, tp)++)


const float[7] DENSITIES = {
    0.5f, 0.3f, 0.15f, 0.1f, 0.1f, 0.08f, 0.05f
};

typedef enum direction_e {
    NO_DIRECTION = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4
} drection_t;

const len_t DIRECTIONS[4][2] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

typedef struct player_s {
    bool is_egg;
    team_t team;
    len_t x;
    len_t y;
    direction_t direction;
    tile_t inventory;
} player_t;

#define PLAYER_IS_AT(pl, x, y) (pl.x == x && pl.y == y)

typedef enum pcommand_e {
    NONE_CMD = 0,
    FORWARD_CMD = 1,
    RIGHT_CMD = 2,
    LEFT_CMD = 3,
    LOOK_CMD = 4,
    INVENTORY_CMD = 5,
    BROADCAST_CMD = 6,
    CONNECT_CMD = 7,
    FORK_CMD = 8,
    EJECT_CMD = 9,
    DEATH_CMD = 10, // gneh
    TAKE_CMD = 11,
    SET_CMD = 12,
    INCANTATION_CMD = 13
} pcommand_t;

const char *COMMAND_LINES[13] = {
    "Forward",
    "Right",
    "Left",
    "Look",
    "Inventory",
    "Broadcast",
    "Connect_nbr",
    "Fork",
    "Eject",
    "",
    "Take",
    "Set",
    "Incantation"
};

const unsigned int COMMAND_TIMES[13] = {
    7, 7, 7, 7, 1, 7, 0, 42, 7, 0, 7, 7, 300
};

typedef struct trantor_s {
    len_t width;
    len_t height;
    tile_t *tiles;
} trantor_t;
