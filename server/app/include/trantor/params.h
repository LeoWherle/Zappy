/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params header
*/

#pragma once

#include "trantor/common.h"
#include "vector.h"

#include <stdbool.h>

// 2 ?
#define MINIMUM_TEAMS 1

typedef struct trantor_params_s {
    unsigned int port;
    len_t width;
    len_t height;
    unsigned int teams;
    vector_t *team_names;
    unsigned int players;
    float f;
} trantor_params_t;

bool parse_args(int ac, char **av, trantor_params_t *params);
void destroy_params(trantor_params_t *params);
int get_team_index(trantor_params_t *params, const char *team_name);
