/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_dtor
*/

#include "vector.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void vec_reset(vector_t *vec)
{
    size_t i = 0;

    if (vec == NULL || !vec->items) {
        return;
    }
    if (vec->dtor != NULL) {
        for (; i < vec->nmemb; i++) {
            vec->dtor(VEC_AT(vec, i));
        }
    }
    free(vec->items);
    vec->items = NULL;
    vec->nmemb = 0;
    vec->capacity = 0;
}

void vec_delete(vector_t *vec)
{
    vec_reset(vec);
    free(vec);
}

void vec_clear(vector_t *vec)
{
    size_t i = 0;

    if (vec == NULL) {
        return;
    }
    if (vec->dtor != NULL) {
        for (; i < vec->nmemb; i++) {
            vec->dtor(VEC_AT(vec, i));
        }
    }
    memset(vec->items, 0, VEC_BYTES_LEFT(vec, 0));
    vec->nmemb = 0;
}

void vec_retain_if(vector_t *vec, bool (*fun)(const void *))
{
    size_t i = 0;
    size_t j = 0;
    bool ret = false;

    if (vec == NULL || fun == NULL)
        return;
    for (; i < vec->nmemb; i++) {
        ret = fun(VEC_AT(vec, i));
        if (ret) {
            memcpy(VEC_AT(vec, j), VEC_AT(vec, i), vec->item_size);
            j++;
        }
        if (!ret && vec->dtor != NULL) {
            vec->dtor(VEC_AT(vec, i));
        }
    }
    memset(VEC_AT(vec, j), 0, VEC_BYTES_LEFT(vec, j));
    vec->nmemb = j;
}

static void vec_remove_if_dup(vector_t *vec,
    bool (*eq)(const void *, const void *), size_t original, size_t other)
{
    if (eq(VEC_AT(vec, original), VEC_AT(vec, other))) {
        if (vec->dtor != NULL) {
            vec->dtor(VEC_AT(vec, other));
        }
        memmove(VEC_AT(vec, other), VEC_AT(vec, other + 1),
            VEC_BYTES_LEFT(vec, other));
        vec->nmemb--;
    }
}

void vec_dedup(vector_t *vec, bool (*eq)(const void *, const void *))
{
    size_t i = 0;
    size_t j = 0;

    if (vec == NULL || eq == NULL) {
        return;
    }
    for (; i < vec->nmemb; i++) {
        for (j = vec->nmemb - 1; j > i; j--) {
            vec_remove_if_dup(vec, eq, i, j);
        }
    }
}
