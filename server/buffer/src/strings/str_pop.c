/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_pop
*/

#include "buffer.h"
#include "sstrings.h"
#include "vector.h"
#include <string.h>

#pragma GCC diagnostic ignored "-Wunused-result"

char str_pop(string_t *str)
{
    vector_t *vec = (vector_t *) str;
    char c;

    if (vec->nmemb == 0) {
        return '\0';
    }
    c = ((char *) vec->items)[vec->nmemb - 1];
    vec->nmemb--;
    return c;
}

void str_truncate(string_t *str, size_t new_size)
{
    vector_t *vec = (vector_t *) str;

    if (new_size >= vec->nmemb) {
        return;
    }
    memset((char *)vec->items + new_size, '\0', vec->nmemb - new_size);
    vec->nmemb = new_size;
}

buf_error_t str_erase(string_t *str, size_t start, size_t end)
{
    vector_t *vec = (vector_t *) str;

    return vec_erase(vec, start, end);
}

char str_remove(string_t *str, size_t pos)
{
    vector_t *vec = (vector_t *) str;
    char c;

    if (pos >= vec->nmemb) {
        return '\0';
    }
    c = ((char *) vec->items)[pos];
    vec_erase(vec, pos, pos + 1);
    return c;
}
