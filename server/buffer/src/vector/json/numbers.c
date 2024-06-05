/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** numbers
*/

#include "vector/json.h"

void jsn_obj_fprint_int(file_data_t file, const char *name, int *value)
{
    if (name == NULL)
        JFPRINTF(file, "%d", *value);
    else
        JFPRINTF(file, "\"%s\": %d", name, *value);
}

void jsn_obj_fprint_float(file_data_t file, const char *name, float *value)
{
    if (name == NULL)
        JFPRINTF(file, "%f", *value);
    else
        JFPRINTF(file, "\"%s\": %f", name, *value);
}

void jsn_obj_fprint_double(file_data_t file, const char *name, double *value)
{
    if (name == NULL)
        JFPRINTF(file, "%f", *value);
    else
        JFPRINTF(file, "\"%s\": %f", name, *value);
}

void jsn_obj_fprint_long(file_data_t file, const char *name, long *value)
{
    if (name == NULL)
        JFPRINTF(file, "%ld", *value);
    else
        JFPRINTF(file, "\"%s\": %ld", name, *value);
}
