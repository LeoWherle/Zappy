/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** number_typedef
*/

#include "vector/json.h"

void jsn_obj_fprint_uint32_t(
    file_data_t file, const char *name, uint32_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "%u", *value);
    else
        JFPRINTF(file, "\"%s\": %u", name, *value);
}

void jsn_obj_fprint_uint64_t(
    file_data_t file, const char *name, uint64_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "%lu", *value);
    else
        JFPRINTF(file, "\"%s\": %lu", name, *value);
}

void jsn_obj_fprint_int32_t(file_data_t file, const char *name, int32_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "%d", *value);
    else
        JFPRINTF(file, "\"%s\": %d", name, *value);
}

void jsn_obj_fprint_int64_t(file_data_t file, const char *name, int64_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "%ld", *value);
    else
        JFPRINTF(file, "\"%s\": %ld", name, *value);
}

void jsn_obj_fprint_size_t(file_data_t file, const char *name, size_t *value)
{
    if (name == NULL)
        JFPRINTF(file, "%lu", *value);
    else
        JFPRINTF(file, "\"%s\": %lu", name, *value);
}
