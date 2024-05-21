/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params header
*/

#pragma once

#include "trantor/common.h"

#include <stdbool.h>

typedef struct trantor_params_s {
    len_t width;
    len_t height;
    unsigned int teams;
    char **team_names;
    unsigned int players;
    float f;
} trantor_params_t;

bool parse_args(int ac, char **av, trantor_params_t *params);
