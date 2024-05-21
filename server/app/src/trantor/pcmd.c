/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd.h"
#include <string.h>
#include <stdlib.h>

const char *PCOMMAND_LINES[PCMD_COUNT] = {
    "", "Forward", "Right", "Left", "Look", "Inventory", "Broadcast",
    "Connect_nbr", "Fork", "Eject", "Take", "Set", "Incantation"
};

const unsigned int PCOMMAND_TIMES[PCMD_COUNT] = {
    0, 7, 7, 7, 7, 1, 7, 0, 42, 7, 7, 7, 300
};

pcmd_func_t COMMAND_FUNCS[PCMD_COUNT] = {
    player_error, player_forward, player_right, player_left, player_look,
    player_inventory, player_broadcast, player_co_num, player_fork,
    player_eject, player_take, player_set, player_incantation
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

pcmd_executor_t *create_pcmd_executor(
    player_t *player, const char *pcmd, float f)
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
    executor->exec_time_left = PCOMMAND_TIMES[executor->command] / f;
    return executor;
}
