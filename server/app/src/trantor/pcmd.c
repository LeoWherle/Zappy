/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd.h"
#include <string.h>

const char *PCOMMAND_LINES[PCMD_COUNT] = {
    "", "Forward", "Right", "Left", "Look", "Inventory", "Broadcast",
    "Connect_nbr", "Fork", "Eject", "Take", "Set", "Incantation"
};

// arg is use to harvest the broadcast msg
pcommand_t parse_pcmd(const char *pcmd, char **arg)
{
    for (int i = 1; i < PCMD_COUNT; i++) {
        if (strncmp(pcmd, PCOMMAND_LINES[i], strlen(PCOMMAND_LINES[i])) != 0)
            continue;
        if (i == BROADCAST_PCMD) {
            *arg = strdup(pcmd + strlen(PCOMMAND_LINES[i]) + 1);
        }
        return i;
    }
    return NONE_PCMD;
}
