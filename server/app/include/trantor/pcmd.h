/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player commands header
*/

#pragma once

#include "trantor/player.h"
#include "trantor/map.h"

#include <string.h>

#define SAY_OK(res) (res = strdup("ok"))
#define SAY_KO(res) (res = strdup("ko"))

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

typedef struct pcmd_executor_s {
    pcommand_t command;
    char *arg;
    player_t *player;
    float exec_time_left;
} pcmd_executor_t;

typedef struct broadcast_buffer_s {
    len_t pos[2];
    char *msg;
} broadcast_buffer_t;  // gneh

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
void player_death(pcmd_args_t *args, char **response);
void player_take(pcmd_args_t *args, char **response);
void player_set(pcmd_args_t *args, char **response);
void player_incantation(pcmd_args_t *args, char **response);
pcommand_t parse_pcmd(const char *pcmd, char **arg);
pcmd_executor_t *create_pcmd_executor(player_t *player, const char *pcmd, float f);
