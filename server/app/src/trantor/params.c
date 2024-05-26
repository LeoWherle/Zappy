/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params source file
*/

#include "trantor/params.h"
#include "serrorh.h"

#include <stdlib.h>
#include <string.h>

// original idea by lucien :
// return -1 if port is invalid else the port as an int (with strtol)
static signed int get_port(const char *port)
{
    char *endptr = NULL;
    long port_int = strtol(port, &endptr, 10);

    if (port_int < 0 || port_int > 65535 || (*endptr) != '\0') {
        LOG_ERROR("Invalid port: \"%s\"", port);
        return -1;
    }
    return port_int;
}

static bool parse_port_arg(int *ac, char ***args, trantor_params_t *params)
{
    signed int port = 0;

    if (*ac < 2 || strcmp((*args)[0], "-p") != 0)
        return false;
    port = get_port((*args)[1]);
    if (port == -1)
        return false;
    params->port = (int) port;
    *ac -= 2;
    *args += 2;
    return true;
}

static bool parse_int_arg(int *ac, char ***args, trantor_params_t *params)
{
    char flags[3][3] = {"-x", "-y", "-c"};
    unsigned int *values[] =
        {&params->width, &params->height, &params->players};

    if (*ac < 2)
        return false;
    for (int i = 0; i < 3; i++) {
        if (strcmp((*args)[0], flags[i]) != 0)
            continue;
        *values[i] = atoi((*args)[1]);
        *ac -= 2;
        *args += 2;
        return true;
    }
    return false;
}

static bool parse_float_arg(int *ac, char ***args, trantor_params_t *params)
{
    if (*ac < 2)
        return false;
    if (strcmp((*args)[0], "-f") != 0)
        return false;
    params->f = atof((*args)[1]);
    *ac -= 2;
    *args += 2;
    return true;
}

static bool parse_str_arg(int *ac, char ***args, trantor_params_t *params)
{
    if (*ac < 1 + MINIMUM_TEAMS)
        return false;
    if (strcmp((*args)[0], "-n") != 0)
        return false;
    while (*ac > 1 && (*args)[1][0] != '-') {
        if (vec_push(params->team_names, (*args)[1]) != BUF_OK)
            return false;
        *ac -= 1;
        *args += 1;
    }
    *ac -= 1;
    *args += 1;
    params->teams = params->team_names->nmemb;
    return true;
}

bool parse_args(int ac, char **av, trantor_params_t *params)
{
    params->team_names = vec_new(sizeof(char *), NULL, NULL);
    if (ac < 3)
        return false;
    while (ac > 1) {
        if (parse_int_arg(&ac, &av, params))
            continue;
        if (parse_float_arg(&ac, &av, params))
            continue;
        if (parse_str_arg(&ac, &av, params))
            continue;
        if (parse_port_arg(&ac, &av, params))
            continue;
        return false;
    }
    return true;
}

void destroy_params(trantor_params_t *params)
{
    vec_delete(params->team_names);
}

int get_team_index(trantor_params_t *params, const char *team_name)
{
    for (unsigned int i = 0; i < params->team_names->nmemb; i++) {
        if (strcmp(team_name, (char *)vec_at(params->team_names, i)) == 0)
            return i;
    }
    return -1;
}
