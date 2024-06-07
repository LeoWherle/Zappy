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
    size_t len = strlen(env);

    if (env != NULL && len > 0) {
        if (strncasecmp(env, "false", len - 1) == 0
            || strncasecmp(env, "0", len - 1) == 0
            || strncasecmp(env, "n", len - 1) == 0
            || strncasecmp(env, "null", len - 1) == 0
            || strncasecmp(env, "no", len - 1) == 0
            || strncasecmp(env, "off", len - 1) == 0) {
            global_log_color(false, 1);
        } else {
            global_log_color(true, 1);
        }
    }
}
