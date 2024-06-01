/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_ctor
*/

#include "buffer.h"
#include "sstrings.h"
#include "vector.h"
#include <string.h>

string_t *str_new(void)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    return (string_t *) vec;
}

string_t *str_from_cstr(const char *cstr)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);
    string_t *str = (string_t *) vec;

    if (str) {
        if (str_push_cstr(str, cstr) == BUF_OK) {
            return str;
        }
    }
    return NULL;
}

buf_error_t str_init(string_t *str, const char *cstr)
{
    if (str->items == NULL) {
        if (vec_init((vector_t *) str, sizeof(char), NULL, NULL) != BUF_OK) {
            return BUF_ALLOC;
        }
    }
    if (cstr == NULL)
        return BUF_OK;
    return str_push_cstr(str, cstr);
}
