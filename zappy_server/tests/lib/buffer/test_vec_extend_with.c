/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_extend_with
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wunused-result"

struct my_struct {
    int a;
    int b;
};

Test(vec_extend_with, test_vec_extend_with)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    for (int i = 0; i < 10; i++) {
        vec_push_int(vec, i);
    }
    int epitech = 42;
    vec_extend_with(vec, &epitech, 42);
    cr_assert_eq(vec->nmemb, 52);
    for (int i = 0; i < 10; i++) {
        cr_assert_eq(*vec_at_int(vec, i), i);
    }
    for (int i = 10; i < 52; i++) {
        cr_assert_eq(*vec_at_int(vec, i), 42);
    }
    vec_delete(vec);
}

static void my_struct_cptor(void *dest, const void *src)
{
    struct my_struct *s1 = dest;
    const struct my_struct *s2 = src;

    s1->a = s2->a;
    s1->b = s2->b;
}

Test(vec_extend_with, test_vec_extend_with_struct)
{
    vector_t *vec = vec_new(sizeof(struct my_struct), NULL, &my_struct_cptor);
    struct my_struct s1 = {1, 2};
    struct my_struct s2 = {3, 4};
    struct my_struct s3 = {5, 6};

    vec_push(vec, &s1);
    vec_push(vec, &s2);
    vec_push(vec, &s3);
    struct my_struct s4 = {7, 8};
    vec_extend_with(vec, &s4, 42);
    cr_assert_eq(vec->nmemb, 45);
    cr_assert_eq(((struct my_struct *)vec_at(vec, 0))->a, 1);
    cr_assert_eq(((struct my_struct *)vec_at(vec, 0))->b, 2);
    cr_assert_eq(((struct my_struct *)vec_at(vec, 1))->a, 3);
    cr_assert_eq(((struct my_struct *)vec_at(vec, 1))->b, 4);
    cr_assert_eq(((struct my_struct *)vec_at(vec, 2))->a, 5);
    cr_assert_eq(((struct my_struct *)vec_at(vec, 2))->b, 6);
    for (int i = 3; i < 45; i++) {
        cr_assert_eq(((struct my_struct *)vec_at(vec, i))->a, 7);
        cr_assert_eq(((struct my_struct *)vec_at(vec, i))->b, 8);
    }
    vec_delete(vec);
}
