/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** number_typedef
*/

#include "vector/json.h"


void jsn_obj_fprint_uint32_t(FILE *file, const char *name, uint32_t *value)
{
    if (name == NULL)
        fprintf(file, "%u", *value);
    else
        fprintf(file, "\"%s\": %u", name, *value);
}

void jsn_obj_fprint_uint64_t(FILE *file, const char *name, uint64_t *value)
{
    if (name == NULL)
        fprintf(file, "%lu", *value);
    else
        fprintf(file, "\"%s\": %lu", name, *value);
}

void jsn_obj_fprint_int32_t(FILE *file, const char *name, int32_t *value)
{
    if (name == NULL)
        fprintf(file, "%d", *value);
    else
        fprintf(file, "\"%s\": %d", name, *value);
}

void jsn_obj_fprint_int64_t(FILE *file, const char *name, int64_t *value)
{
    if (name == NULL)
        fprintf(file, "%ld", *value);
    else
        fprintf(file, "\"%s\": %ld", name, *value);
}

void jsn_obj_fprint_size_t(FILE *file, const char *name, size_t *value)
{
    if (name == NULL)
        fprintf(file, "%lu", *value);
    else
        fprintf(file, "\"%s\": %lu", name, *value);
}
