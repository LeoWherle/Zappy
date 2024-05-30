/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player commands header
*/

#pragma once

#include "trantor/common.h"
#include "trantor/item.h"

#define PCMD_COUNT 13

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
    TAKE_PCMD = 10,
    SET_PCMD = 11,
    INCANTATION_PCMD = 12
} pcommand_t;

#define PCMD_NEEDS_OBJ(c) (c == 10 || c == 11)

typedef struct broadcast_buffer_s {
    len_t pos[2];
    char *msg;
} broadcast_buffer_t;  // gneh

pcommand_t parse_pcmd(const char *pcmd, char **arg, item_t *item);
