/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** load_color
*/

#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

#include "serrorh.h"

bool global_log_color(bool no_color, bool set)
{
    static bool color = true;

    if (set) {
        color = no_color;
    }
    return color;
}

void load_env_log_color(void)
{
    char *env = getenv(LOG_COLOR_ENV);

    if (env != NULL) {
        if (!strcasecmp(env, "false") || !strcasecmp(env, "0")
            || !strcasecmp(env, "n") || !strcasecmp(env, "null")
            || !strcasecmp(env, "no") || !strcasecmp(env, "off")) {
            global_log_color(true, 1);
        } else {
            global_log_color(false, 1);
        }
    }
}