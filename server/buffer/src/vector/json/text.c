/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** strings
*/

#include "vector/json.h"

void jsn_obj_fprint_string_t(FILE *file, const char *name, string_t *value)
{
    if (name == NULL) {
        fprintf(file, "\"%.*s\"", (int) value->nmemb, (char *) value->items);
    } else {
        fprintf(file, "\"%s\": \"%.*s\"", name, (int) value->nmemb,
            (char *) value->items);
    }
}

void jsn_obj_fprint_cstring_t(FILE *file, const char *name, cstring_t *value)
{
    if (name == NULL)
        fprintf(file, "\"%s\"", *value);
    else
        fprintf(file, "\"%s\": \"%s\"", name, *value);
}

void jsn_obj_fprint_char(FILE *file, const char *name, char *value)
{
    if (name == NULL)
        fprintf(file, "\"%c\"", *value);
    else
        fprintf(file, "\"%s\": \"%c\"", name, *value);
}
