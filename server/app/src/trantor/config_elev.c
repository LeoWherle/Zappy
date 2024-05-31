/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd source file
*/

#include "trantor/config.h"

const elev_config_t ELEVATION_CONFIG[MAX_LEVEL] = {
    {0, {{0, 0, 0, 0, 0, 0, 0}}},
    {1, {{0, 1, 0, 0, 0, 0, 0}}},
    {2, {{0, 1, 1, 1, 0, 0, 0}}},
    {2, {{0, 2, 0, 1, 0, 2, 0}}},
    {4, {{0, 1, 1, 2, 0, 1, 0}}},
    {4, {{0, 1, 2, 1, 3, 0, 0}}},
    {6, {{0, 1, 2, 3, 0, 1, 0}}},
    {6, {{0, 2, 2, 2, 2, 2, 1}}}
};

unsigned int get_elev_players(unsigned int level)
{
    return ELEVATION_CONFIG[level - 1].players;
}

const tile_t *get_elev_stones(unsigned int level)
{
    return &ELEVATION_CONFIG[level - 1].stones;
}
