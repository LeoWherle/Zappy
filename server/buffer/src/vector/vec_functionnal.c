/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_functionnal
*/

#include "vector.h"
// Disable unused-result warning because we preallocate the vector with
// vec_reserve before pushing
#pragma GCC diagnostic ignored "-Wunused-result"

vector_t *vec_map(const vector_t *vec, const map_fn_t fun)
{
    vector_t *new_vec = NULL;
    size_t i = 0;
    void *ret = NULL;

    if (vec == NULL || fun == NULL)
        return NULL;
    new_vec = vec_new(vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL)
        return NULL;
    for (; i < vec->nmemb; i++) {
        ret = fun(VEC_AT(vec, i));
        if (ret == NULL) {
            vec_delete(new_vec);
            return NULL;
        }
        vec_push(new_vec, ret);
    }
    return new_vec;
}

vector_t *vec_map_arg(const vector_t *vec, const map_fn_arg_t fun, void *arg)
{
    vector_t *new_vec = NULL;
    size_t i = 0;
    void *ret = NULL;

    if (vec == NULL || fun == NULL)
        return NULL;
    new_vec = vec_new(vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL)
        return NULL;
    for (; i < vec->nmemb; i++) {
        ret = fun(VEC_AT(vec, i), arg);
        if (ret == NULL) {
            vec_delete(new_vec);
            return NULL;
        }
        (void) vec_push(new_vec, ret);
    }
    return new_vec;
}

vector_t *vec_filter(const vector_t *vec, const filter_fn_t fun)
{
    vector_t *new_vec = NULL;
    size_t i = 0;
    bool ret = NULL;

    if (vec == NULL || fun == NULL)
        return NULL;
    new_vec = vec_new(vec->item_size, vec->dtor, vec->cpctor);
    if (new_vec == NULL)
        return NULL;
    if (vec_reserve(new_vec, vec->nmemb) != BUF_OK) {
        vec_delete(new_vec);
        return NULL;
    }
    for (; i < vec->nmemb; i++) {
        ret = fun(VEC_AT(vec, i));
        if (ret) {
            (void) vec_push(new_vec, VEC_AT(vec, i));
        }
    }
    return new_vec;
}
