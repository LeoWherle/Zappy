/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd_exec.h"
#include "trantor/config.h"


void init_pcmd_executor(const char *pcmd, pcmd_executor_t *res)
{
    res->command = parse_pcmd(pcmd, &(res->arg), &(res->item));
    res->exec_time_left += get_pcmd_time(res->command);
}
