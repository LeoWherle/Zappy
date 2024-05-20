/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_add
*/

#include "vector.h"

buf_error_t vec_push_int(vector_t *vec, int elem)
{
    return (vec_push(vec, &elem));
}

buf_error_t vec_push_char(vector_t *vec, char elem)
{
    return (vec_push(vec, &elem));
}

buf_error_t vec_push_float(vector_t *vec, float elem)
{
    return (vec_push(vec, &elem));
}

buf_error_t vec_push_double(vector_t *vec, double elem)
{
    return (vec_push(vec, &elem));
}
