/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** array
*/

#include "vector/json.h"

void json_print_vec(file_data_t file, const char *name, vector_t *vec,
    void (*print)(file_data_t, char *, void *))
{
    void *data = NULL;

    JSON_ARR_BEGIN(file, name);
    for (size_t i = 0; i < vec->nmemb; i++) {
        data = VEC_AT(vec, i);
        print(file, NULL, data);
        if (i < vec->nmemb - 1)
            JSON_ARR_SEP(file);
    }
    JSON_ARR_END(file);
}
