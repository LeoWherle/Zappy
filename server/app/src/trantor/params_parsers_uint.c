/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params source file
*/

#include "trantor/params.h"
#include "serrorh.h"

#include <stdlib.h>
#include <time.h>

static bool parse_uint_arg(
    int *ac, char ***args, const char *flag, unsigned int *val)
{
    int atoi_res = -1;

    if (*ac < 2)
        return false;
    atoi_res = atoi((*args)[1]);
    if (atoi_res < 0) {
        LOG_ERROR("Invalid value for flag \"%s\": \"%s\"", flag, (*args)[1]);
        return false;
    }
    *val = (unsigned int) atoi_res;
    *ac -= 2;
    *args += 2;
    return true;
}

bool parse_width_arg(int *ac, char ***args, trantor_params_t *params)
{
    return parse_uint_arg(ac, args, "-x", &params->width);
}

bool parse_height_arg(int *ac, char ***args, trantor_params_t *params)
{
    return parse_uint_arg(ac, args, "-y", &params->height);
}

bool parse_players_arg(int *ac, char ***args, trantor_params_t *params)
{
    return parse_uint_arg(ac, args, "-c", &params->players);
}

bool parse_seed_arg(int *ac, char ***args, trantor_params_t *params)
{
    bool res = parse_uint_arg(ac, args, "-s", &params->seed);

    if (res && params->seed == 0) {
        params->seed = (unsigned int) time(NULL);
    }
    return res;
}
