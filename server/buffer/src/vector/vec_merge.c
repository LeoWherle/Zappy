/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_merge
*/

#include "vector.h"
#include <string.h>
#pragma GCC diagnostic ignored "-Wunused-result"

buf_error_t vec_append(vector_t *dest, vector_t *src)
{
    size_t i = 0;

    if (dest == NULL || src == NULL) {
        return (BUF_NULLPTR);
    }
    if (vec_reserve(dest, src->nmemb) != BUF_OK) {
        return (BUF_ALLOC);
    }
    for (; i < src->nmemb; i++) {
        vec_push(dest, VEC_AT(src, i));
    }
    vec_clear(src);
    return (BUF_OK);
}

buf_error_t vec_append_array(
    vector_t *dest, const void *buf, size_t nmemb, size_t item_size)
{
    size_t i = 0;

    if (dest == NULL || buf == NULL) {
        return (BUF_NULLPTR);
    }
    if (vec_reserve(dest, nmemb + 1) != BUF_OK) {
        return (BUF_ALLOC);
    }
    for (; i < nmemb; i++) {
        (void) vec_push(dest, buf + i * item_size);
    }
    return (BUF_OK);
}

vector_t *vec_split_off(vector_t *vec, size_t index)
{
    vector_t *new_vec = NULL;

    if (vec == NULL || index > vec->nmemb) {
        return (NULL);
    }
    new_vec = vec_with_capacity(
        vec->nmemb - index, vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL) {
        return (NULL);
    }
    memcpy(new_vec->items, VEC_AT(vec, index), VEC_BYTES_LEFT(vec, index));
    new_vec->nmemb = vec->nmemb - index;
    memset(VEC_AT(vec, index), 0, VEC_BYTES_LEFT(vec, index));
    vec->nmemb = index;
    return (new_vec);
}
