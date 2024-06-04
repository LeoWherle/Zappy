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

#define PARSER_FUNC_COUNT 9

typedef struct trantor_params_s {
    int port;
    len_t width;
    len_t height;
    unsigned int teams;
    vector_t team_names;
    unsigned int players;
    float f;
    bool spam_gui;
    unsigned int seed;
    bool paused_start;
} trantor_params_t;

// typedef for arg parsing funcs
typedef bool (*parse_arg_func_t)(
    int *ac, char ***args, trantor_params_t *params);

typedef struct arg_parser_s {
    const char *flag;
    parse_arg_func_t func;
    bool required;
} arg_parser_t;


void destroy_params(trantor_params_t *params);
int get_team_index(trantor_params_t *params, const char *team_name);
/**
 * @brief returns a c_str from the vector, DO NOT Modify the params, after
 * getting the c_string.
 */
const char *get_team_name(const trantor_params_t *params, team_t team_id);


// Internal
bool parse_width_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_height_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_players_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_seed_arg(int *ac, char ***args, trantor_params_t *params);

bool parse_port_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_float_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_teams_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_spam_gui_arg(int *ac, char ***args, trantor_params_t *params);
bool parse_paused_arg(int *ac, char ***args, trantor_params_t *params);
