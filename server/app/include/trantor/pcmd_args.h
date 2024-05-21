/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player commands args header
*/

#pragma once

#include "trantor/player.h"
#include "trantor/map.h"

typedef struct pcmd_args_s {
    player_t *player;
    union {
        map_t *map;
        char *broadcast_msg;
    };
} pcmd_args_t;

typedef void (*pcmd_func_t)(pcmd_args_t *args, char **response);

void player_error(pcmd_args_t *args, char **response);
void player_forward(pcmd_args_t *args, char **response);
void player_right(pcmd_args_t *args, char **response);
void player_left(pcmd_args_t *args, char **response);
void player_look(pcmd_args_t *args, char **response);
void player_inventory(pcmd_args_t *args, char **response);
void player_broadcast(pcmd_args_t *args, char **response);
void player_co_num(pcmd_args_t *args, char **response);
void player_fork(pcmd_args_t *args, char **response);
void player_eject(pcmd_args_t *args, char **response);
void player_take(pcmd_args_t *args, char **response);
void player_set(pcmd_args_t *args, char **response);
void player_incantation(pcmd_args_t *args, char **response);
