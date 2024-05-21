/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_utils
*/

#include "sstrings.h"
#include "vector.h"

vector_t *str_to_vec(string_t *str)
{
    return (vector_t *) str;
}

string_t *str_split_off(string_t *str, size_t index)
{
    vector_t *vec = (vector_t *) str;
    vector_t *new_vec = vec_split_off(vec, index);

    return (string_t *) new_vec;
}
