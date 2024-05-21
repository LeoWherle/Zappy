/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_pop_push
*/

#include "vector.h"
#include <string.h>

buf_error_t vec_push(vector_t *vec, const void *item)
{
    if (vec == NULL || item == NULL) {
        return (BUF_NULLPTR);
    }
    if (vec_reserve(vec, 1) != BUF_OK) {
        return (BUF_ALLOC);
    }
    if (vec->cpctor != NULL) {
        vec->cpctor(VEC_AT(vec, vec->nmemb), item);
    } else {
        memcpy(VEC_AT(vec, vec->nmemb), item, vec->item_size);
    }
    vec->nmemb++;
    return (BUF_OK);
}

buf_error_t vec_pop(vector_t *vec)
{
    if (vec == NULL) {
        return (BUF_NULLPTR);
    }
    if (vec->nmemb == 0) {
        return (BUF_EMPTY);
    }
    if (vec->dtor != NULL) {
        vec->dtor(VEC_AT(vec, vec->nmemb - 1));
    }
    vec->nmemb--;
    return (BUF_OK);
}
