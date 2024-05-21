/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_display
*/

#include "vector.h"
#include <stdio.h>

void vec_print(const vector_t *vec, void (*print)(const void *),
    const char *sep, const char *end)
{
    size_t i = 0;
    const char *default_sep = "";

    if (vec == NULL || print == NULL) {
        return;
    }
    if (sep == NULL)
        sep = ", ";
    printf("[");
    for (; i < vec->nmemb; i++) {
        printf("%s", default_sep);
        print(VEC_AT(vec, i));
        default_sep = sep;
    }
    printf("]");
    if (end != NULL) {
        printf("%s", end);
    } else {
        printf("\n");
    }
}

void vec_display(const vector_t *vec, void (*print)(const void *),
    const char *sep, void (*put)(const char *))
{
    size_t i = 0;
    const char *default_sep = "";

    if (vec == NULL || print == NULL) {
        return;
    }
    if (sep == NULL)
        sep = ", ";
    put("[");
    for (; i < vec->nmemb; i++) {
        put(default_sep);
        print(VEC_AT(vec, i));
        default_sep = sep;
    }
    put("]");
}
