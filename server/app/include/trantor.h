/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor header
*/

#pragma once

#include "vector.h"

// in case we want to change
typedef unsigned int quant_t;
typedef unsigned int len_t;
typedef unsigned int team_t;
typedef unsigned int elevation_t;

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
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
} drection_t;

const int DIRECTIONS[4][2] = {
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
    elevation_t elevation;
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

const char *COMMAND_LINES[14] = {
    "",
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

#define CMD_NAME_LEN(cmd) (strlen(COMMAND_LINES[cmd]))

const unsigned int COMMAND_TIMES[14] = {
    0, 7, 7, 7, 7, 1, 7, 0, 42, 7, 0, 7, 7, 300
};

typedef struct map_s {
    len_t width;
    len_t height;
    tile_t *tiles;
} map_t;

bool player_move(player_t *player, map_t *map, direction_t direction)
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
    return true;
}

typedef struct pcmd_args_s {
    player_t *player;
    union {
        map_t *map;
        char *broadcast_msg;
    };
} pcmd_args_t;

#define SAY_OK(res) (res = strdup("ok"))
#define SAY_KO(res) (res = strdup("ko"))

typedef bool (*pcmd_func_t)(pcmd_args_t *args, char **response);

bool player_forward(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    return player_move(args->player, args->map, args->player->direction);
}

bool player_right(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    args->player->direction = (args->player->direction + 1) % 4;
    return true;
}

bool player_left(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    args->player->direction = (args->player->direction + 3) % 4;
    return true;
}

bool player_look(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

bool player_inventory(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

typedef struct broadcast_buffer_s {
    len_t[2] pos;
    char *msg;
} broadcast_buffer_t;  // gneh

bool player_broadcast(pcmd_args_t *args, char **response)
{
    broadcast_buffer_t *buf = (broadcast_buffer_t *) response;

    buf->pos[0] = args->player->x;
    buf->pos[1] = args->player->y;
    buf->msg = args->broadcast_msg;
    return true;
}

bool player_co_num(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

bool player_fork(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    // not implemented
    return true;
}

bool player_eject(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

bool player_death(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

bool player_take(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

bool player_set(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

bool player_incantation(pcmd_args_t *args, char **response)
{
    // not implemented
    return true;
}

pcmd_func_t COMMAND_FUNCS[13] = {
    NULL,
    player_forward,
    player_right,
    player_left,
    player_look,
    player_inventory,
    player_broadcast,
    player_co_num,
    player_fork,
    player_eject,
    player_death,
    player_take,
    player_set,
    player_incantation
};

// arg is use to harvest the broadcast msg
pcommand_t parse_pcmd(const char *pcmd, char **arg)
{
    for (int i = 1; i < 14; i++) {
        if (strncmp(pcmd, COMMAND_LINES[i], CMD_NAME_LEN(i)) != 0)
            continue;
        if (i == BROADCAST_CMD) {
            *arg = strdup(pcmd + CMD_NAME_LEN(i) + 1);
        }
        return i;
    }
    return NONE_CMD;
}

typedef struct pcmd_executor_s {
    pcommand_t command;
    char *arg;
    player_t *player;
    float exec_time_left;
} pcmd_executor_t;

pcmd_executor_t *create_pcmd_executor(player_t *player, const char *pcmd, float f)
{
    char *arg = NULL;
    pcommand_t command;
    pcmd_executor_t *executor = NULL;

    command = parse_pcmd(pcmd, &arg);
    if (command == NONE_CMD)
        return NULL;
    executor = malloc(sizeof(pcmd_executor_t));
    executor->command = command;
    executor->arg = arg;
    executor->player = player;
    executor->exec_time_left = COMMAND_TIMES[executor->command] / f;
    return executor;
}