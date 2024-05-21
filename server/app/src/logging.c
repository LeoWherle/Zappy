/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** logging
*/

#include "serrorh.h"
#include <stdio.h>

void init_logging(const char *env_file)
{
    if (load_env(env_file) == -1) {
        printf("%s\n", "No such env file");
        return;
    }
    load_env_log_level();
}
