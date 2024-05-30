/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player header
*/

#pragma once

#include "trantor/common.h"
#include "trantor/direction.h"
#include "trantor/map.h"
#include "trantor/tile.h"
#include "trantor/pcmd_exec.h"

#include "sstrings.h"
#include <stdbool.h>

#define PLAYER_IS_AT(pl, x, y) (pl.x == x && pl.y == y)

typedef struct player_s player_t;

struct player_s {
    bool is_egg;
    team_t team;
    coord_t coord;
    direction_t direction;
    tile_t inventory;
    elevation_t elevation;
    string_t *pcmd_buffer; // stores received commands
    unsigned int npcmd;
    string_t *response_buffer; // stores responses
    bool busy;
    pcmd_executor_t pcmd_exec;
    player_t *incantator;
    unsigned int n;
    double time_left;
    bool is_dead;
};

void init_egg(player_t *player, team_t team, coord_t c);
void hatch_egg(player_t *player, double f);
void destroy_player(void *player);
