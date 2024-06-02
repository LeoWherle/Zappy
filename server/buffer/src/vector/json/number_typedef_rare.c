/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** number_typedef_rare
*/

#include "vector/json.h"

void jsn_obj_fprint_ssize_t(FILE *file, const char *name, ssize_t *value)
{
    if (name == NULL)
        fprintf(file, "%ld", *value);
    else
        fprintf(file, "\"%s\": %ld", name, *value);
}

void jsn_obj_fprint_bool(FILE *file, const char *name, bool *value)
{
    if (name == NULL)
        fprintf(file, "%s", *value ? "true" : "false");
    else
        fprintf(file, "\"%s\": %s", name, *value ? "true" : "false");
}

void jsn_obj_fprint__Bool(FILE *file, const char *name, bool *value)
{
    jsn_obj_fprint_bool(file, name, value);
}
