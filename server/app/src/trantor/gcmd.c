/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands source file
*/

#include "trantor/gcmd.h"
#include "trantor/config.h"

#include <stdlib.h>


// WRONG (2nd atoi for bct)
gcommand_t parse_gcmd(const char *gcmd, gcmd_args_t *args)
{
    size_t slen = 0;
    gcommand_t gcmd_type = get_gcmd_by_name(gcmd);

    if (gcmd_type == NONE_GCMD)
        return NONE_GCMD;
    if (gcmd_type == BCT_GCMD || USES_N(gcmd_type) || gcmd_type == SST_GCMD)
        slen = get_gcmd_name_len(gcmd_type) + 1;
    if (gcmd_type == BCT_GCMD) {
        args->pos[0] = atoi(gcmd + slen);
        args->pos[1] = atoi(gcmd + slen);
    }
    if (USES_N(gcmd_type))
        args->n = atoi(gcmd + slen);
    if (gcmd_type == SST_GCMD)
        args->t = atof(gcmd + slen);
    return gcmd_type;
}
