/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_delete
*/

#include "vector.h"
#include <stdlib.h>

int vec_swap_remove_int(vector_t *vec, size_t index)
{
    void *elem = NULL;
    int ret = 0;

    elem = vec_swap_remove(vec, index);
    if (elem == NULL)
        return (0);
    ret = *(int *) elem;
    free(elem);
    return ret;
}

char vec_swap_remove_char(vector_t *vec, size_t index)
{
    void *elem = NULL;
    char ret = 0;

    elem = vec_swap_remove(vec, index);
    if (elem == NULL)
        return (0);
    ret = *(char *) elem;
    free(elem);
    return ret;
}

float vec_swap_remove_float(vector_t *vec, size_t index)
{
    void *elem = NULL;
    float ret = 0;

    elem = vec_swap_remove(vec, index);
    if (elem == NULL)
        return (0);
    ret = *(float *) elem;
    free(elem);
    return ret;
}

double vec_swap_remove_double(vector_t *vec, size_t index)
{
    void *elem = NULL;
    double ret = 0;

    elem = vec_swap_remove(vec, index);
    if (elem == NULL)
        return (0);
    ret = *(double *) elem;
    free(elem);
    return ret;
}
