/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** vec_pos
*/

#include "vector.h"
#include <sys/select.h>
#include <unistd.h>

ssize_t vec_indexof(const vector_t *vec, const void *elem)
{
    size_t i = 0;

    if (vec == NULL || elem == NULL)
        return (-1);
    for (i = 0; i < vec->nmemb; i++) {
        if (VEC_AT(vec, i) == elem) {
            return (i);
        }
    }
    return (-1);
}
