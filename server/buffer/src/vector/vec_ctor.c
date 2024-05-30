/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vector
*/

#include "vector.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

buf_error_t vec_init(
    vector_t *vec, size_t elem_size, dtor_t dtor, cpctor_t cpctor)
{
    if (vec == NULL) {
        return (BUF_NULLPTR);
    }
    vec->dtor = dtor;
    vec->cpctor = cpctor;
    vec->item_size = elem_size;
    vec->items = calloc(VEC_INIT_CAPACITY, elem_size);
    if (vec->items == NULL) {
        return (BUF_ALLOC);
    }
    vec->nmemb = 0;
    vec->capacity = VEC_INIT_CAPACITY;
    return (BUF_OK);
}

vector_t *vec_new(size_t elem_size, dtor_t dtor, cpctor_t cpctor)
{
    vector_t *vec = NULL;

    vec = malloc(sizeof(vector_t));
    if (vec_init(vec, elem_size, dtor, cpctor) == BUF_OK) {
        return (vec);
    }
    free(vec);
    return (NULL);
}

buf_error_t vec_reserve(vector_t *vec, size_t additional)
{
    u_char *items_new = NULL;
    size_t new_capacity = 0;

    if (vec == NULL) {
        return (BUF_NULLPTR);
    }
    new_capacity = vec->nmemb + additional;
    if (new_capacity > vec->capacity) {
        new_capacity *= 2;
        items_new = reallocarray(vec->items, new_capacity, vec->item_size);
        if (items_new == NULL) {
            return (BUF_ALLOC);
        }
        vec->capacity = new_capacity;
        vec->items = items_new;
    }
    return (BUF_OK);
}

vector_t *vec_with_capacity(
    size_t size, size_t elem_size, dtor_t dtor, cpctor_t cpctor)
{
    vector_t *vec = NULL;

    vec = vec_new(elem_size, dtor, cpctor);
    if (vec == NULL) {
        return (NULL);
    }
    if (vec_reserve(vec, size) != BUF_OK) {
        vec_delete(vec);
        return (NULL);
    }
    return (vec);
}
