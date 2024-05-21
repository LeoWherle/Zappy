/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player source file
*/

#include "trantor/pcmd.h"


const char *PCOMMAND_LINES[14] = {
    "", "Forward", "Right", "Left", "Look", "Inventory", "Broadcast",
    "Connect_nbr", "Fork", "Eject", "", "Take", "Set", "Incantation"
};


const unsigned int PCOMMAND_TIMES[14] = {
    0, 7, 7, 7, 7, 1, 7, 0, 42, 7, 0, 7, 7, 300
};

pcmd_func_t COMMAND_FUNCS[13] = {
    NULL, player_forward, player_right, player_left, player_look,
    player_inventory, player_broadcast, player_co_num, player_fork,
    player_eject, player_death, player_take, player_set, player_incantation
};

// arg is use to harvest the broadcast msg
pcommand_t parse_pcmd(const char *pcmd, char **arg)
{
    for (int i = 1; i < 14; i++) {
        if (strncmp(pcmd, COMMAND_LINES[i], strlen(COMMAND_LINES[i])) != 0)
            continue;
        if (i == BROADCAST_PCMD) {
            *arg = strdup(pcmd + strlen(COMMAND_LINES[i]) + 1);
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
    executor->exec_time_left = COMMAND_TIMES[executor->command] / f;
    return executor;
}
