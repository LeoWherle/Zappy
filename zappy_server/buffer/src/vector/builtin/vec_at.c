/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_at
*/

#include "vector.h"

int *vec_at_int(const vector_t *vec, size_t index)
{
    return (vec_at(vec, index));
}

char *vec_at_char(const vector_t *vec, size_t index)
{
    return (vec_at(vec, index));
}

float *vec_at_float(const vector_t *vec, size_t index)
{
    return (vec_at(vec, index));
}

double *vec_at_double(const vector_t *vec, size_t index)
{
    return (vec_at(vec, index));
}
