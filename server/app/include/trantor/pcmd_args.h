/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player commands args header
*/

#pragma once

#include "trantor/item.h"
#include "trantor/player.h"
#include "trantor/map.h"

#include <string.h>

typedef struct pcmd_args_s {
    player_t *player;
    map_t *map;
    char *broadcast_msg;
    item_t item;
    vector_t *players;
    unsigned int cnb;
    string_t *log;
} pcmd_args_t;

typedef void (*pcmd_func_t)(pcmd_args_t *args);

void player_error(pcmd_args_t *args);
void player_forward(pcmd_args_t *args);
void player_right(pcmd_args_t *args);
void player_left(pcmd_args_t *args);
void player_look(pcmd_args_t *args);
void player_inventory(pcmd_args_t *args);
void player_broadcast(pcmd_args_t *args);
void player_co_num(pcmd_args_t *args);
void player_fork(pcmd_args_t *args);
void player_eject(pcmd_args_t *args);
void player_take(pcmd_args_t *args);
void player_set(pcmd_args_t *args);
void player_incantation(pcmd_args_t *args);

// Extra for pre-check
bool can_invocate(vector_t *players, player_t *invocator, map_t *map);
