/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd_exec.h"

const unsigned int PCOMMAND_TIMES[PCMD_COUNT] = {
    0, 7, 7, 7, 7, 1, 7, 0, 42, 7, 7, 7, 300
};

void init_pcmd_executor(const char *pcmd, float f, pcmd_executor_t *res)
{
    res->command = parse_pcmd(pcmd, &(res->arg), &(res->item));
    res->exec_time_left = PCOMMAND_TIMES[res->command] / f;
}
