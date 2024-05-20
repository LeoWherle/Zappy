/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_sort
*/

#include "vector.h"
#include <stdlib.h>
#include <sys/types.h>

void vec_sort(vector_t *vec, int (*cmp)(const void *, const void *))
{
    if (vec == NULL || cmp == NULL)
        return;
    qsort(vec->items, vec->nmemb, vec->item_size, cmp);
}
