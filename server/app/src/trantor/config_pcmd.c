/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/config.h"

const pcmd_config_t PCOMMAND_CONFIG[PCMD_COUNT] = {
    {NONE_PCMD, "", 0, player_error},
    {FORWARD_PCMD, "Forward", 7, player_forward},
    {RIGHT_PCMD, "Right", 7, player_right},
    {LEFT_PCMD, "Left", 7, player_left},
    {LOOK_PCMD, "Look", 7, player_look},
    {INVENTORY_PCMD, "Inventory", 1, player_inventory},
    {BROADCAST_PCMD, "Broadcast", 7, player_broadcast},
    {CONNECT_PCMD, "Connect_nbr", 0, player_co_num},
    {FORK_PCMD, "Fork", 42, player_fork},
    {EJECT_PCMD, "Eject", 7, player_eject},
    {TAKE_PCMD, "Take", 7, player_take},
    {SET_PCMD, "Set", 7, player_set},
    {INCANTATION_PCMD, "Incantation", 300, player_incantation}
};

const char *get_pcmd_name(pcommand_t pcmd)
{
    return PCOMMAND_CONFIG[pcmd].name;
}

size_t get_pcmd_name_len(pcommand_t pcmd)
{
    return strlen(PCOMMAND_CONFIG[pcmd].name);
}

unsigned int get_pcmd_time(pcommand_t pcmd)
{
    return PCOMMAND_CONFIG[pcmd].time;
}

pcmd_func_t get_pcmd_func(pcommand_t pcmd)
{
    return PCOMMAND_CONFIG[pcmd].func;
}

pcommand_t get_pcmd_by_name(const char *name)
{
    for (int i = 1; i < PCMD_COUNT; i++) {
        if (strncmp(name, PCOMMAND_CONFIG[i].name,
            strlen(PCOMMAND_CONFIG[i].name)) == 0)
            return i;
    }
    return NONE_PCMD;
}
