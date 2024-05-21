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
    vector_t *pcmd_buffer; // stores received commands
    vector_t *response_buffer; // stores responses
    bool busy;
} player_t;

void init_player(player_t *player, team_t team, len_t x, len_t y)
{
    player->is_egg = false;
    player->team = team;
    player->x = x;
    player->y = y;
    player->direction = UP;
    for (int i = 0; i < 7; i++) {
        player->inventory.items[i] = 0;
    }
    player->elevation = 1;
    pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    response_buffer = vec_new(sizeof(char *), NULL, NULL);
    busy = false;
}

void init_egg(player_t *player, team_t team, len_t x, len_t y)
{
    player->is_egg = true;
    player->team = team;
    player->x = x;
    player->y = y;
}

void hatch_egg(player_t *player)
{
    player->is_egg = false;
    player->direction = UP; // MAKE RANDOM
    player->elevation = 1;
    pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    response_buffer = vec_new(sizeof(char *), NULL, NULL);
    busy = false;
}

void destroy_player(player_t *player)
{
    vec_delete(player->pcmd_buffer);
}

#define PLAYER_IS_AT(pl, x, y) (pl.x == x && pl.y == y)

typedef enum pcommand_e {
    NONE_PCMD = 0,
    FORWARD_PCMD = 1,
    RIGHT_PCMD = 2,
    LEFT_PCMD = 3,
    LOOK_PCMD = 4,
    INVENTORY_PCMD = 5,
    BROADCAST_PCMD = 6,
    CONNECT_PCMD = 7,
    FORK_PCMD = 8,
    EJECT_PCMD = 9,
    DEATH_PCMD = 10, // gneh
    TAKE_PCMD = 11,
    SET_PCMD = 12,
    INCANTATION_PCMD = 13
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

#define PCMD_NAME_LEN(cmd) (strlen(COMMAND_LINES[cmd]))

const unsigned int COMMAND_TIMES[14] = {
    0, 7, 7, 7, 7, 1, 7, 0, 42, 7, 0, 7, 7, 300
};

typedef struct map_s {
    len_t width;
    len_t height;
    tile_t *tiles;
} map_t;

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

typedef struct pcmd_args_s {
    player_t *player;
    union {
        map_t *map;
        char *broadcast_msg;
    };
} pcmd_args_t;

#define SAY_OK(res) (res = strdup("ok"))
#define SAY_KO(res) (res = strdup("ko"))

typedef void (*pcmd_func_t)(pcmd_args_t *args, char **response);

void player_error(pcmd_args_t *args, char **response)
{
    SAY_KO(*response);
}

void player_forward(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    player_move(args->player, args->map, args->player->direction);
}

void player_right(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    args->player->direction = (args->player->direction + 1) % 4;
}

void player_left(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    args->player->direction = (args->player->direction + 3) % 4;
}

void player_look(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_inventory(pcmd_args_t *args, char **response)
{
    // not implemented
}

typedef struct broadcast_buffer_s {
    len_t[2] pos;
    char *msg;
} broadcast_buffer_t;  // gneh

void player_broadcast(pcmd_args_t *args, char **response)
{
    broadcast_buffer_t *buf = (broadcast_buffer_t *) response;

    buf->pos[0] = args->player->x;
    buf->pos[1] = args->player->y;
    buf->msg = args->broadcast_msg;
}

void player_co_num(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_fork(pcmd_args_t *args, char **response)
{
    SAY_OK(*response);
    // not implemented
}

void player_eject(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_death(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_take(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_set(pcmd_args_t *args, char **response)
{
    // not implemented
}

void player_incantation(pcmd_args_t *args, char **response)
{
    // not implemented
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
        if (strncmp(pcmd, COMMAND_LINES[i], PCMD_NAME_LEN(i)) != 0)
            continue;
        if (i == BROADCAST_PCMD) {
            *arg = strdup(pcmd + PCMD_NAME_LEN(i) + 1);
        }
        return i;
    }
    return NONE_PCMD;
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
    if (command == NONE_PCMD)
        return NULL;
    executor = malloc(sizeof(pcmd_executor_t));
    executor->command = command;
    executor->arg = arg;
    executor->player = player;
    executor->exec_time_left = COMMAND_TIMES[executor->command] / f;
    return executor;
}

typedef struct trantor_params_s {
    len_t width;
    len_t height;
    unsigned int teams;
    char **team_names;
    unsigned int players;
    float f;
} trantor_params_t;

bool parse_args(int ac, char **av, trantor_params_t *params)
{
    // not implemented
    return true;
}

typedef struct trantor_s {
    trantor_params_t params;
    map_t map;
    vector_t players;
    vector_t player_executors;
    vector_t log;
} trantor_t;

void init_trantor(trantor_t *trantor, trantor_params_t *params)
{
    trantor->params = *params;
    init_map(params->width, params->height, &trantor->map);
    trantor->free_players = vec_new(sizeof(player_t), NULL, destroy_player);
    trantor->player_executors = vec_new(sizeof(pcmd_executor_t), NULL, NULL);
}

void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->free_players);
    vec_delete(trantor->player_executors);
}

typedef enum gcommand_e {
    NONE_GCMD = 0,
    MSZ_GCMD = 1,
    BCT_GCMD = 2,
    MCT_GCMD = 3,
    TNA_GCMD = 4,
    PPO_GCMD = 5,
    PLV_GCMD = 6,
    PIN_GCMD = 7,
    SGT_GCMD = 8,
    SST_GCMD = 9
} gcommand_t;

#define USES_N(cmd) (cmd == PPO_GCMD || cmd == PLV_GCMD || cmd == PIN_GCMD)

const char *GCOMMAND_LINES[10] = {
    "", "msz", "bct", "mct", "tna", "ppo", "plv", "pin", "sgt", "sst"
};

#define GCMD_NAME_LEN(cmd) (strlen(GCOMMAND_LINES[cmd]))

typedef union gcmd_args_u {
    len_t[2] pos;
    unsigned int n;
    float t;
} gcmd_args_t;

typedef void (*gcmd_func_t)(trantor_t *trantor, gcmd_args_t *args);

void gui_error(trantor_t *trantor, gcmd_args_t *args)
{
    vec_push(&trantor->log, strdup("suc"));
}

void gui_msz(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    asprintf(&msg, "msz %d %d", trantor->map.width, trantor->map.height);
    vec_push(&trantor->log, msg);
}

void gui_bct(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    tile_t *tile =
        &trantor->map.tiles[args->pos[1] * trantor->map.width + args->pos[0]];

    asprintf(&msg, "bct %d %d %d %d %d %d %d %d %d",
        args->pos[0], args->pos[1],
        tile->items[0], tile->items[1], tile->items[2], tile->items[3],
        tile->items[4], tile->items[5], tile->items[6]);
    vec_push(&trantor->log, msg);
}

void gui_mct(trantor_t *trantor, gcmd_args_t *args)
{
    gcmd_args_t args;

    for (len_t y = 0; y < trantor->map.height; y++) {
        for (len_t x = 0; x < trantor->map.width; x++) {
            args.pos = {x, y};
            gui_bct(trantor, &args);
        }
    }
}

void gui_tna(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    for (unsigned int i = 0; i < trantor->params.teams; i++) {
        asprintf(&msg, "tna %s", trantor->params.team_names[i]);
        vec_push(&trantor->log, msg);
    }
}

void gui_ppo(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    player_t *player = vec_get(&trantor->players, args->n);

    asprintf(&msg, "ppo %d %d %d %d", args->n,
        player->x, player->y, player->direction + 1);
    vec_push(&trantor->log, msg);
}

void gui_plv(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    player_t *player = vec_get(&trantor->players, args->n);

    asprintf(&msg, "plv %d %d", args->n, player->elevation);
    vec_push(&trantor->log, msg);
}

void gui_pin(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    player_t *player = vec_get(&trantor->players, args->n);

    asprintf(&msg, "pin %d %d %d %d %d %d %d %d %d %d",
        args->n, player->x, player->y, player->inventory.items[0],
        player->inventory.items[1], player->inventory.items[2],
        player->inventory.items[3], player->inventory.items[4],
        player->inventory.items[5], player->inventory.items[6]);
    vec_push(&trantor->log, msg);
}

void gui_sgt(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    asprintf(&msg, "sgt %f", 0.0f); // replace by actual time or f ?
    vec_push(&trantor->log, msg);
}

void gui_sst(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    asprintf(&msg, "sst %f", 0.0f); // same
    vec_push(&trantor->log, msg);
}

gcmd_func_t GCOMMAND_FUNCS[10] = {
    gui_error, gui_msz, gui_bct, gui_mct, gui_tna,
    gui_ppo, gui_plv, gui_pin, gui_sgt, gui_sst
};

gcommand_t parse_gcmd(const char *gcmd, gcmd_args_t *args)
{
    for (int i = 1; i < 10; i++) {
        if (strncmp(gcmd, GCOMMAND_LINES[i], GCMD_NAME_LEN(i)) != 0)
            continue;
        if (i == BCT_GCMD) {
            args->pos[0] = atoi(gcmd + GCMD_NAME_LEN(i) + 1);
            args->pos[1] = atoi(gcmd + GCMD_NAME_LEN(i) + 3); // WRONG
        }
        if (USES_N(i))
            args->n = atoi(gcmd + GCMD_NAME_LEN(i) + 1);
        if (i == SST_GCMD)
            args->t = atof(gcmd + GCMD_NAME_LEN(i) + 1);
        return i;
    }
    return NONE_GCMD;
}

player_t *get_team_egg(vector_t *players, const char *team)
{
    for (unsigned int i = 0; i < players->size; i++) {
        player_t *player = vec_get(players, i);

        if (player->is_egg && strcmp(player->team, team) == 0)
            return player;
    }
    return NULL;
}

void player_feed_trantor_line(player_t *player, trantor_t *trantor, const char *line)
{
    // not implemented
}

void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
    // not implemented
}
