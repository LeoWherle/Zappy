/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** load_env
*/

#include "serrorh.h"

__attribute__((constructor))
void pre_load_env(void)
{
    if (load_env(ENV_FILE_DEFAULT)) {
        return;
    }
    load_env_log_level();
    load_env_log_file();
}

__attribute__((destructor))
void post_load_env(void)
{
    FILE *file = global_log_file(false, NULL);

    if (file != NULL) {
        fclose(file);
    }
}
