/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** vec_insert_bytes
*/

#include "vector.h"
#include <string.h>

buf_error_t vec_insert_bytes(
    vector_t *vec, const void *buf, size_t nmemb, size_t index)
{
    if (index > vec->nmemb) {
        return BUF_INDEX;
    }
    if (vec_reserve(vec, vec->nmemb + nmemb) != BUF_OK) {
        return BUF_ALLOC;
    }
    memmove((char *) vec->items + (index + nmemb) * vec->item_size,
        (char *) vec->items + index * vec->item_size,
        (vec->nmemb - index) * vec->item_size);
    memcpy((char *) vec->items + index * vec->item_size, buf,
        nmemb * vec->item_size);
    vec->nmemb += nmemb;
    return BUF_OK;
}
