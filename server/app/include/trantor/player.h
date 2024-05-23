/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player header
*/

#pragma once

#include "trantor/common.h"
#include "trantor/direction.h"
#include "trantor/tile.h"
#include "trantor/pcmd_exec.h"

#include "vector.h"
#include <stdbool.h>

#define PLAYER_IS_AT(pl, x, y) (pl.x == x && pl.y == y)

typedef struct player_s player_t;

struct player_s {
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
    pcmd_executor_t pcmd_exec;
    player_t *incantator;
};

void init_egg(player_t *player, team_t team, len_t x, len_t y);
void hatch_egg(player_t *player);
void destroy_player(void *player);
