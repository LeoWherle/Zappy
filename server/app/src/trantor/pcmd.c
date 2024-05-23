/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd.h"
#include "trantor/tile.h"
#include <string.h>

const char *ITEM_NMES[7] = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
};

const char *PCOMMAND_LINES[PCMD_COUNT] = {
    "", "Forward", "Right", "Left", "Look", "Inventory", "Broadcast",
    "Connect_nbr", "Fork", "Eject", "Take", "Set", "Incantation"
};

static item_t get_item_type(const char *item)
{
    for (int i = 0; i < 7; i++) {
        if (strcmp(item, ITEM_NMES[i]) == 0)
            return i + 1;
    }
    return NONE_ITEM;
}

// arg is use to harvest the broadcast msg
pcommand_t parse_pcmd(const char *pcmd, char **arg, item_t *item)
{
    for (int i = 1; i < PCMD_COUNT; i++) {
        if (strncmp(pcmd, PCOMMAND_LINES[i], strlen(PCOMMAND_LINES[i])) != 0)
            continue;
        if (i == BROADCAST_PCMD)
            *arg = strdup(pcmd + strlen(PCOMMAND_LINES[i]) + 1);
        if (PCMD_NEEDS_OBJ(i))
            *item = get_item_type(pcmd + strlen(PCOMMAND_LINES[i]) + 1);
        if (PCMD_NEEDS_OBJ(i) && *item == NONE_ITEM)
            return NONE_PCMD;
        return i;
    }
    return NONE_PCMD;
}
