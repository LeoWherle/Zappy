/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** vec_erase
*/

#include "vector.h"
#include <string.h>

static void remove_if(
    vector_t *vec, bool (*predicate)(void *), size_t elem_pos)
{
    if (predicate(VEC_AT(vec, elem_pos))) {
        if (vec->dtor != NULL) {
            vec->dtor(VEC_AT(vec, elem_pos));
        }
        memmove(VEC_AT(vec, elem_pos), VEC_AT(vec, elem_pos + 1),
            (vec->nmemb - elem_pos - 1) * vec->item_size);
        vec->nmemb--;
    }
}

void vec_remove_if(vector_t *vec, bool (*predicate)(void *))
{
    size_t i = 0;

    if (vec == NULL || predicate == NULL)
        return;
    for (i = 0; i < vec->nmemb; i++) {
        remove_if(vec, predicate, i);
    }
}

buf_error_t vec_erase(vector_t *vec, size_t start, size_t end)
{
    size_t i = 0;

    if (vec == NULL || start > vec->nmemb || end > vec->nmemb)
        return (BUF_NULLPTR);
    for (i = start; i < end; i++) {
        if (vec->dtor != NULL) {
            vec->dtor(VEC_AT(vec, i));
        }
    }
    memmove(VEC_AT(vec, start), VEC_AT(vec, end),
        (vec->nmemb - (end - start)) * vec->item_size);
    vec->nmemb -= end - start;
    return (BUF_OK);
}
