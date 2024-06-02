/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** numbers
*/

#include "vector/json.h"

void jsn_obj_fprint_int(FILE *file, const char *name, int *value)
{
    if (name == NULL)
        fprintf(file, "%d", *value);
    else
        fprintf(file, "\"%s\": %d", name, *value);
}

void jsn_obj_fprint_float(FILE *file, const char *name, float *value)
{
    if (name == NULL)
        fprintf(file, "%f", *value);
    else
        fprintf(file, "\"%s\": %f", name, *value);
}

void jsn_obj_fprint_double(FILE *file, const char *name, double *value)
{
    if (name == NULL)
        fprintf(file, "%f", *value);
    else
        fprintf(file, "\"%s\": %f", name, *value);
}

void jsn_obj_fprint_long(FILE *file, const char *name, long *value)
{
    if (name == NULL)
        fprintf(file, "%ld", *value);
    else
        fprintf(file, "\"%s\": %ld", name, *value);
}
