/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands source file
*/

#include "trantor/gcmd.h"

#include <string.h>
#include <stdlib.h>

const char *GCOMMAND_LINES[10] = {
    "", "msz", "bct", "mct", "tna", "ppo", "plv", "pin", "sgt", "sst"
};

// WRONG (2nd atoi for bct)
gcommand_t parse_gcmd(const char *gcmd, gcmd_args_t *args)
{
    for (int i = 1; i < 10; i++) {
        if (strncmp(gcmd, GCOMMAND_LINES[i], strlen(GCOMMAND_LINES[i])) != 0)
            continue;
        if (i == BCT_GCMD) {
            args->pos[0] = atoi(gcmd + strlen(GCOMMAND_LINES[i]) + 1);
            args->pos[1] = atoi(gcmd + strlen(GCOMMAND_LINES[i]) + 3);
        }
        if (USES_N(i))
            args->n = atoi(gcmd + strlen(GCOMMAND_LINES[i]) + 1);
        if (i == SST_GCMD)
            args->t = atof(gcmd + strlen(GCOMMAND_LINES[i]) + 1);
        return i;
    }
    return NONE_GCMD;
}
