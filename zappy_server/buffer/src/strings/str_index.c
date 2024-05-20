/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_index
*/

#include "buffer.h"
#include "sstrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str_at(const string_t *this, size_t pos)
{
    if (pos >= this->nmemb) {
        fprintf(stderr, "Index out of bounds\n");
        abort();
    }
    return ((char *) this->items)[pos];
}

buf_error_t str_insert(string_t *str, size_t index, char c)
{
    vector_t *vec = (vector_t *) str;

    return vec_insert(vec, &c, index);
}

buf_error_t str_insert_bytes(
    string_t *str, size_t index, const void *bytes, size_t nmemb)
{
    vector_t *vec = (vector_t *) str;

    if (index > vec->nmemb) {
        return BUF_INDEX;
    }
    return vec_insert_bytes(vec, bytes, nmemb, index);
}

buf_error_t str_insert_cstr(string_t *str, size_t index, const char *cstr)
{
    vector_t *vec = (vector_t *) str;

    return vec_insert_bytes(vec, cstr, strlen(cstr), index);
}

buf_error_t str_insert_str(string_t *str, size_t index, const string_t *other)
{
    vector_t *vec = (vector_t *) str;

    return vec_insert_bytes(vec, other->items, other->nmemb, index);
}
