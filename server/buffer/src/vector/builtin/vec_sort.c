/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_sort
*/

#include "vector.h"

static int int_cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

static int char_cmp(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

static int float_cmp(const void *a, const void *b)
{
    return (*(float *)a - *(float *)b);
}

static int double_cmp(const void *a, const void *b)
{
    return (*(double *)a - *(double *)b);
}

void vec_sort_int(vector_t *vec)
{
    vec_sort(vec, &int_cmp);
}

void vec_sort_char(vector_t *vec)
{
    vec_sort(vec, &char_cmp);
}

void vec_sort_float(vector_t *vec)
{
    vec_sort(vec, &float_cmp);
}

void vec_sort_double(vector_t *vec)
{
    vec_sort(vec, &double_cmp);
}
