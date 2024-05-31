/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/config.h"

const item_config_t ITEM_CONFIG[ITEM_COUNT] = {
    {NONE_ITEM, "", 0.0f},
    {FOOD_ITEM, "food", 0.5f},
    {LINEMATE_ITEM, "linemate", 0.3f},
    {DERAUMERE_ITEM, "deraumere", 0.15f},
    {SIBUR_ITEM, "sibur", 0.1f},
    {MENDIANE_ITEM, "mendiane", 0.1f},
    {PHIRAS_ITEM, "phiras", 0.08f},
    {THYSTAME_ITEM, "thystame", 0.05f}
};

const char *get_item_name(item_t item)
{
    return ITEM_CONFIG[item].name;
}

size_t get_item_name_len(item_t item)
{
    return strlen(ITEM_CONFIG[item].name);
}

float get_item_density(item_t item)
{
    return ITEM_CONFIG[item].density;
}

item_t get_item_by_name(const char *name)
{
    for (int i = 1; i < ITEM_COUNT; i++) {
        if (strncmp(name, ITEM_CONFIG[i].name,
            strlen(ITEM_CONFIG[i].name)) == 0)
            return i;
    }
    return NONE_ITEM;
}
