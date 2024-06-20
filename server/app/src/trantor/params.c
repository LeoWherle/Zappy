/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor params source file
*/

#include "trantor/params.h"
#include "serrorh.h"
#include "trantor/common.h"
#include "trantor/config.h"
#include "vector.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

const arg_parser_t ARGS_PARSERS[PARSER_FUNC_COUNT] = {
    {"-p", parse_port_arg, false},
    {"-x", parse_width_arg, false},
    {"-y", parse_height_arg, false},
    {"-c", parse_players_arg, false},
    {"-s", parse_seed_arg, false},
    {"-f", parse_float_arg, false},
    {"-n", parse_teams_arg, true},
    {"--spam-gui", parse_spam_gui_arg, false},
    {"--paused", parse_paused_arg, false}
};

static void set_args_to_default(trantor_params_t *params)
{
    params->port = DEFAULT_PORT;
    params->width = DEFAULT_WIDTH;
    params->height = DEFAULT_HEIGHT;
    params->players = DEFAULT_PLAYERS;
    params->f = DEFAULT_F;
    params->spam_gui = false;
    params->seed = (unsigned int) time(NULL);
    params->paused_start = false;
    if (vec_init(&params->team_names, sizeof(char *), NULL, NULL) != BUF_OK)
        LOG_ERROR("Failed to init team_names vector");
}

static bool parse_arg(
    int *ac, char ***args, trantor_params_t *params, bool *parsed)
{
    for (int i = 0; i < PARSER_FUNC_COUNT + 1; i++) {
        if (i == PARSER_FUNC_COUNT) {
            LOG_ERROR("Invalid argument: \"%s\"", (*args)[0]);
            return false;
        }
        if (strcmp((*args)[0], ARGS_PARSERS[i].flag) != 0)
            continue;
        if (parsed[i]) {
            LOG_ERROR("Duplicate argument: \"%s\"", (*args)[0]);
            return false;
        }
        if (!ARGS_PARSERS[i].func(ac, args, params))
            return false;
        parsed[i] = true;
        return true;
    }
    return false;
}

bool parse_args(int ac, char **av, trantor_params_t *params)
{
    bool parsed[PARSER_FUNC_COUNT] = {false};

    set_args_to_default(params);
    while (ac != 0)
        if (!parse_arg(&ac, &av, params, parsed))
            return false;
    for (int i = 0; i < PARSER_FUNC_COUNT; i++) {
        if (ARGS_PARSERS[i].required && !parsed[i]) {
            LOG_ERROR("Missing required argument");
            return false;
        }
    }
    return true;
}

void destroy_params(trantor_params_t *params)
{
    vec_reset(&params->team_names);
}

int get_team_index(trantor_params_t *params, const char *team_name)
{
    for (unsigned int i = 0; i < params->team_names.nmemb; i++) {
        if (strcmp(team_name, (char *) vec_at(&params->team_names, i)) == 0)
            return i;
    }
    return -1;
}

const char *get_team_name(const trantor_params_t *params, team_t team_id)
{
    return (const char *) vec_at(&params->team_names, (size_t) team_id);
}
