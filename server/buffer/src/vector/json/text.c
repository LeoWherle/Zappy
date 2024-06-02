/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** strings
*/

#include "vector/json.h"

void jsn_obj_fprint_string_t(
    file_data_t file, const char *name, string_t *value)
{
    if (name == NULL) {
        JFPRINTF(file, "\"%.*s\"", (int) value->nmemb, (char *) value->items);
    } else {
        JFPRINTF(file, "\"%s\": \"%.*s\"", name, (int) value->nmemb,
            (char *) value->items);
    }
}

void jsn_obj_fprint_cstring_t(
    file_data_t file, const char *name, cstring_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "\"%s\"", *value);
    else
        JFPRINTF(file, "\"%s\": \"%s\"", name, *value);
}

void jsn_obj_fprint_char(file_data_t file, const char *name, char *value)
{
    if (name == NULL)
        JFPRINTF(file, "\"%c\"", *value);
    else
        JFPRINTF(file, "\"%s\": \"%c\"", name, *value);
}
