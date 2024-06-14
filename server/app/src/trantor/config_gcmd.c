/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/config.h"

const gcmd_config_t GCOMMAND_CONFIG[GCMD_COUNT] = {
    {NONE_GCMD, "", gui_error},
    {MSZ_GCMD, "msz", gui_msz},
    {BCT_GCMD, "bct", gui_bct},
    {MCT_GCMD, "mct", gui_mct},
    {TNA_GCMD, "tna", gui_tna},
    {PPO_GCMD, "ppo", gui_ppo},
    {PLV_GCMD, "plv", gui_plv},
    {PIN_GCMD, "pin", gui_pin},
    {SGT_GCMD, "sgt", gui_sgt},
    {SST_GCMD, "sst", gui_sst},
    {RST_GCMD, "rst", gui_rst},
    {NXT_GCMD, "nxt", gui_nxt},
    {PSD_GCMD, "psd", gui_psd}
};

const char *get_gcmd_name(gcommand_t gcmd)
{
    return GCOMMAND_CONFIG[gcmd].name;
}

size_t get_gcmd_name_len(gcommand_t gcmd)
{
    return strlen(GCOMMAND_CONFIG[gcmd].name);
}

gcmd_func_t get_gcmd_func(gcommand_t gcmd)
{
    return GCOMMAND_CONFIG[gcmd].func;
}

gcommand_t get_gcmd_by_name(const char *name)
{
    for (int i = 1; i < GCMD_COUNT; i++) {
        if (strncmp(name, GCOMMAND_CONFIG[i].name,
            strlen(GCOMMAND_CONFIG[i].name)) == 0)
            return i;
    }
    return NONE_GCMD;
}
