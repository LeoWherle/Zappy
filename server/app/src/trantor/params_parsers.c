/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params source file
*/

#include "trantor/params.h"
#include "serrorh.h"
#include "vector.h"

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

bool parse_port_arg(int *ac, char ***args, trantor_params_t *params)
{
    signed int port = 0;

    if (*ac < 2)
        return false;
    port = get_port((*args)[1]);
    if (port == -1)
        return false;
    params->port = (int) port;
    *ac -= 2;
    *args += 2;
    return true;
}

bool parse_float_arg(int *ac, char ***args, trantor_params_t *params)
{
    if (*ac < 2)
        return false;
    params->f = atof((*args)[1]);
    *ac -= 2;
    *args += 2;
    return true;
}

static bool parse_team_arg(int *ac, char ***args, trantor_params_t *params)
{
    for (unsigned int i = 0; i < params->team_names.nmemb; i++) {
        if (strcmp((*args)[1], (char *) vec_at(&params->team_names, i)) == 0) {
            LOG_ERROR("Duplicate team name: \"%s\"", (*args)[1]);
            return false;
        }
    }
    if (vec_push(&params->team_names, (*args)[1]) != BUF_OK)
        return false;
    *ac -= 1;
    *args += 1;
    return true;
}

bool parse_teams_arg(int *ac, char ***args, trantor_params_t *params)
{
    if (*ac < 2)
        return false;
    while (*ac > 1 && (*args)[1][0] != '-')
        if (!parse_team_arg(ac, args, params))
            return false;
    *ac -= 1;
    *args += 1;
    params->teams = params->team_names.nmemb;
    return true;
}

bool parse_spam_gui_arg(int *ac, char ***args, trantor_params_t *params)
{
    if (*ac < 1)
        return false;
    params->spam_gui = true;
    *ac -= 1;
    *args += 1;
    return true;
}

bool parse_paused_arg(int *ac, char ***args, trantor_params_t *params)
{
    if (*ac < 1)
        return false;
    params->paused_start = true;
    *ac -= 1;
    *args += 1;
    return true;
}
