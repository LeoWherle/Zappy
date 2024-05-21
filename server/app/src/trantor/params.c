/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params source file
*/

#include "trantor/params.h"

#include <stdlib.h>
#include <string.h>

static bool parse_int_arg(int *ac, char **args, trantor_params_t *params)
{
    char flags[4][3] = {"-p", "-x", "-y", "-c"};
    unsigned int *values[] =
        {&params->port, &params->width, &params->height, &params->players};

    if (*ac < 2)
        return false;
    for (int i = 0; i < 4; i++) {
        if (strcmp(args[0], flags[i]) != 0)
            continue;
        *values[i] = atoi(args[1]);
        *ac -= 2;
        *args += 2;
        return true;
    }
    return false;
}

static bool parse_float_arg(int *ac, char **args, trantor_params_t *params)
{
    if (*ac < 2)
        return false;
    if (strcmp(args[0], "-f") != 0)
        return false;
    params->f = atof(args[1]);
    *ac -= 2;
    *args += 2;
    return true;
}

static bool parse_str_arg(int *ac, char **args, trantor_params_t *params)
{
    if (*ac < 1 + MINIMUM_TEAMS)
        return false;
    if (strcmp(args[0], "-n") != 0)
        return false;
    while (*ac > 1 && strcmp(args[1], "-c") != 0) {
        if (vec_push(params->team_names, strdup(args[1])) != BUF_OK)
            return false;
        *ac -= 1;
        *args += 1;
    }
    params->teams = params->team_names->nmemb;
    return true;
}

bool parse_args(int ac, char **av, trantor_params_t *params)
{
    params->team_names = vec_new(sizeof(char *), free, NULL);
    while (ac > 1) {
        if (parse_int_arg(&ac, av + 1, params))
            continue;
        if (parse_float_arg(&ac, av + 1, params))
            continue;
        if (parse_str_arg(&ac, av + 1, params))
            continue;
        return false;
    }
    return true;
}

void destroy_params(trantor_params_t *params)
{
    vec_delete(params->team_names);
}
