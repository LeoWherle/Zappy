/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_insert
*/

#include "vector.h"

buf_error_t vec_insert_int(vector_t *vec, int elem, size_t index)
{
    return (vec_insert(vec, &elem, index));
}

buf_error_t vec_insert_char(vector_t *vec, char elem, size_t index)
{
    return (vec_insert(vec, &elem, index));
}

buf_error_t vec_insert_float(vector_t *vec, float elem, size_t index)
{
    return (vec_insert(vec, &elem, index));
}

buf_error_t vec_insert_double(vector_t *vec, double elem, size_t index)
{
    return (vec_insert(vec, &elem, index));
}
