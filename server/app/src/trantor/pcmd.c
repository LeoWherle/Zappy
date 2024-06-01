/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/pcmd.h"
#include "trantor/config.h"
#include <string.h>

// arg is use to harvest the broadcast msg or the item name
pcommand_t parse_pcmd(const char *pcmd, char **arg, item_t *item)
{
    size_t slen = 0;
    pcommand_t res = get_pcmd_by_name(pcmd);

    if (res == NONE_PCMD)
        return NONE_PCMD;
    if (res == BROADCAST_PCMD || PCMD_NEEDS_OBJ(res))
        slen = get_pcmd_name_len(res) + 1;
    if (res == BROADCAST_PCMD)
        *arg = strdup(pcmd + slen);
    if (PCMD_NEEDS_OBJ(res))
        *item = get_item_by_name(pcmd + slen);
    if (PCMD_NEEDS_OBJ(res) && *item == NONE_ITEM)
        return NONE_PCMD;
    return res;
}
