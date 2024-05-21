/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** vec_print_int
*/

#include "vector.h"
#include <stdio.h>

static void print_int(const void *elem)
{
    printf("%d", *(int *)elem);
}

static void print_char(const void *elem)
{
    printf("%c", *(char *)elem);
}

static void print_float(const void *elem)
{
    printf("%f", *(float *)elem);
}

static void print_double(const void *elem)
{
    printf("%f", *(double *)elem);
}

void vec_print_int(const vector_t *vec)
{
    vec_print(vec, &print_int, NULL, NULL);
}

void vec_print_char(const vector_t *vec)
{
    vec_print(vec, &print_char, NULL, NULL);
}

void vec_print_float(const vector_t *vec)
{
    vec_print(vec, &print_float, NULL, NULL);
}

void vec_print_double(const vector_t *vec)
{
    vec_print(vec, &print_double, NULL, NULL);
}
