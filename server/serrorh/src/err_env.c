/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** err_env
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int load_env_line(const char *line)
{
    char *new_line = NULL;

    new_line = strchr(line, '\n');
    if (new_line != NULL) {
        *new_line = '\0';
    }
    new_line = strchr(line, '=');
    if (new_line != NULL) {
        *new_line = '\0';
        setenv(line, new_line + 1, 1);
    }
    return 0;
}

// Load environment variables from .env file into the environment
// NULL if no file is provided
int load_env(const char *env_file)
{
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (env_file == NULL)
        return 0;
    file = fopen(env_file, "r");
    if (file == NULL)
        return -1;
    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[0] != '#') {
            load_env_line(line);
        }
        read = getline(&line, &len, file);
    }
    free(line);
    fclose(file);
    return 0;
}
