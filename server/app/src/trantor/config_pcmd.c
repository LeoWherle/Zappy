/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/config.h"

const pcmd_config_t PCOMMAND_CONFIG[PCMD_COUNT] = {
    {NONE_PCMD,        "",            0,   player_error,       ""},
    {FORWARD_PCMD,     "Forward",     7,   player_forward,     "pm %d\n"},
    {RIGHT_PCMD,       "Right",       7,   player_right,       "ptr %d\n"},
    {LEFT_PCMD,        "Left",        7,   player_left,        "ptl %d\n"},
    {LOOK_PCMD,        "Look",        7,   player_look,        "pla %d\n"},
    {INVENTORY_PCMD,   "Inventory",   1,   player_inventory,   ""},
    {BROADCAST_PCMD,   "Broadcast",   7,   player_broadcast,   ""},
    {CONNECT_PCMD,     "Connect_nbr", 0,   player_co_num,      ""},
    {FORK_PCMD,        "Fork",        42,  player_fork,        "pf %d\n"},
    {EJECT_PCMD,       "Eject",       7,   player_eject,       "ppx %d\n"},
    {TAKE_PCMD,        "Take",        7,   player_take,        "pto %d %d\n"},
    {SET_PCMD,         "Set",         7,   player_set,         "pdo %d %d\n"},
    {INCANTATION_PCMD, "Incantation", 300, player_incantation, ""}
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

const char *get_pcmd_anim_ev_fmt(pcommand_t pcmd)
{
    return PCOMMAND_CONFIG[pcmd].anim_ev_fmt;
}
