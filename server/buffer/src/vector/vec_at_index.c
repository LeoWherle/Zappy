/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_remove
*/

#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

buf_error_t vec_insert(vector_t *vec, const void *elem, size_t index)
{
    if (vec == NULL || elem == NULL)
        return (BUF_NULLPTR);
    if (index > vec->nmemb)
        return (BUF_INDEX);
    if (vec_reserve(vec, 1) != BUF_OK)
        return (BUF_ALLOC);
    if (index < vec->nmemb) {
        memmove(VEC_AT(vec, index + 1), VEC_AT(vec, index),
            VEC_BYTES_LEFT(vec, index));
    }
    if (vec->cpctor != NULL) {
        vec->cpctor(VEC_AT(vec, index), elem);
    } else {
        memcpy(VEC_AT(vec, index), elem, vec->item_size);
    }
    vec->nmemb++;
    return (BUF_OK);
}

static void vec_remove_element(vector_t *vec, size_t index, void *item)
{
    if (vec->dtor != NULL) {
        vec->dtor(item);
    }
    if (index != vec->nmemb - 1) {
        memmove(item, item + vec->item_size, VEC_BYTES_LEFT(vec, index + 1));
    }
    vec->nmemb--;
}

static bool is_valid_index(const vector_t *vec, size_t index)
{
    return (vec != NULL && index < vec->nmemb);
}

buf_error_t vec_delete_at(vector_t *vec, size_t index)
{
    if (!is_valid_index(vec, index)) {
        return (BUF_INDEX);
    }
    vec_remove_element(vec, index, VEC_AT(vec, index));
    return (BUF_OK);
}

void *vec_remove(vector_t *vec, size_t index)
{
    void *item = NULL;
    void *copy = NULL;

    if (!is_valid_index(vec, index)) {
        return (NULL);
    }
    copy = malloc(vec->item_size);
    if (copy == NULL) {
        return (NULL);
    }
    item = VEC_AT(vec, index);
    copy = memcpy(copy, item, vec->item_size);
    vec_remove_element(vec, index, item);
    return (copy);
}

void *vec_swap_remove(vector_t *vec, size_t index)
{
    void *item = NULL;
    void *copy = NULL;

    if (!is_valid_index(vec, index)) {
        return (NULL);
    }
    copy = malloc(vec->item_size);
    if (copy == NULL) {
        return (NULL);
    }
    item = VEC_AT(vec, index);
    copy = memcpy(copy, item, vec->item_size);
    if (vec->dtor != NULL)
        vec->dtor(item);
    if (index != vec->nmemb - 1) {
        memmove(item, VEC_AT(vec, vec->nmemb - 1), vec->item_size);
    }
    vec->nmemb--;
    return (copy);
}

void *vec_at(const vector_t *vec, size_t index)
{
    if (!is_valid_index(vec, index)) {
        return (NULL);
    }
    return (VEC_AT(vec, index));
}
