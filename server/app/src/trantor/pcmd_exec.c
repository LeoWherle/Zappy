/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd_exec.h"
#include "trantor/pcmd_args.h"

const unsigned int PCOMMAND_TIMES[PCMD_COUNT] = {
    0, 7, 7, 7, 7, 1, 7, 0, 42, 7, 7, 7, 300
};

pcmd_func_t COMMAND_FUNCS[PCMD_COUNT] = {
    player_error, player_forward, player_right, player_left, player_look,
    player_inventory, player_broadcast, player_co_num, player_fork,
    player_eject, player_take, player_set, player_incantation
};

void init_pcmd_executor(const char *pcmd, float f, pcmd_executor_t *res)
{
    res->command = parse_pcmd(pcmd, &(res->arg));
    res->exec_time_left = PCOMMAND_TIMES[res->command] / f;
}
