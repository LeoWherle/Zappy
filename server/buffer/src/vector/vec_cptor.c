/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vector
*/

#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

vector_t *vec_clone(const vector_t *vec)
{
    vector_t *new_vec = NULL;

    if (vec == NULL) {
        return (NULL);
    }
    new_vec =
        vec_with_capacity(vec->nmemb, vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL) {
        return (NULL);
    }
    if (vec->cpctor != NULL) {
        for (size_t i = 0; i < vec->nmemb; i++) {
            vec->cpctor(VEC_AT(new_vec, i), VEC_AT(vec, i));
        }
    } else {
        memcpy(new_vec->items, vec->items, vec->nmemb * vec->item_size);
    }
    new_vec->nmemb = vec->nmemb;
    return (new_vec);
}

buf_error_t vec_extend_with(vector_t *vec, const void *element, size_t n)
{
    if (vec == NULL || element == NULL) {
        return (BUF_NULLPTR);
    }
    if (vec_reserve(vec, n) != BUF_OK) {
        return (BUF_ALLOC);
    }
    if (vec->cpctor != NULL) {
        for (size_t i = 0; i < n; i++) {
            vec->cpctor(VEC_AT(vec, vec->nmemb + i), element);
        }
    } else {
        for (size_t i = 0; i < n; i++) {
            memcpy(VEC_AT(vec, vec->nmemb + i), element, vec->item_size);
        }
    }
    vec->nmemb += n;
    return (BUF_OK);
}
