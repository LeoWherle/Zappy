/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/config.h"

pcommand_t get_pcmd_by_name(const char *name)
{
    for (int i = 1; i < PCMD_COUNT; i++) {
        if (strncmp(name, get_pcmd_name(i), get_pcmd_name_len(i)) == 0)
            return i;
    }
    return NONE_PCMD;
}
