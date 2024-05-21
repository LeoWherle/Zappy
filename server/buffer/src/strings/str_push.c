/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_push
*/

#include "sstrings.h"
#include "vector.h"
#include <string.h>

buf_error_t str_push_cstr(string_t *str, const char *cstr)
{
    vector_t *vec = (vector_t *) str;

    return vec_append_array(vec, cstr, strlen(cstr), sizeof(char));
}

buf_error_t str_push_char(string_t *str, char c)
{
    vector_t *vec = (vector_t *) str;

    return vec_push(vec, &c);
}

buf_error_t str_push_str(string_t *str, const string_t *other)
{
    vector_t *vec = (vector_t *) str;

    return vec_append_array(vec, other->items, other->nmemb, sizeof(char));
}

buf_error_t str_push_bytes(string_t *str, const void *bytes, size_t n)
{
    vector_t *vec = (vector_t *) str;

    return vec_append_array(vec, bytes, n, sizeof(char));
}
