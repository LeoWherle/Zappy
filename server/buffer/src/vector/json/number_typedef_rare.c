/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** number_typedef_rare
*/

#include "vector/json.h"

void jsn_obj_fprint_ssize_t(file_data_t file, const char *name, ssize_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "%ld", *value);
    else
        JFPRINTF(file, "\"%s\": %ld", name, *value);
}

void jsn_obj_fprint_bool(file_data_t file, const char *name, bool *value)
{
    if (name == NULL)
        JFPRINTF(file, "%s", *value ? "true" : "false");
    else
        JFPRINTF(file, "\"%s\": %s", name, *value ? "true" : "false");
}

void jsn_obj_fprint__Bool(file_data_t file, const char *name, bool *value)
{
    jsn_obj_fprint_bool(file, name, value);
}
