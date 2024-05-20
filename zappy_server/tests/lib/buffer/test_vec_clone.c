/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_clone
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

struct my_struct {
    int a;
    int b;
};

Test(vec_clone, test_vec_clone)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vector_t *vec2 = NULL;

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    vec2 = vec_clone(vec);
    cr_assert_eq(*vec_at_int(vec2, 0), 1);
    cr_assert_eq(*vec_at_int(vec2, 1), 2);
    cr_assert_eq(*vec_at_int(vec2, 2), 3);
    vec_delete(vec);
    vec_delete(vec2);
}

static void my_struct_cptor(void *dest, const void *src)
{
    struct my_struct *s1 = dest;
    const struct my_struct *s2 = src;

    s1->a = s2->a;
    s1->b = s2->b;
}

Test(vec_clone, test_vec_clone_struct)
{
    vector_t *vec = vec_new(sizeof(struct my_struct), NULL, &my_struct_cptor);
    vector_t *vec2 = NULL;
    struct my_struct s1 = {1, 2};
    struct my_struct s2 = {3, 4};
    struct my_struct s3 = {5, 6};

    vec_push(vec, &s1);
    vec_push(vec, &s2);
    vec_push(vec, &s3);
    vec2 = vec_clone(vec);
    cr_assert_eq(((struct my_struct *)vec_at(vec2, 0))->a, 1);
    cr_assert_eq(((struct my_struct *)vec_at(vec2, 0))->b, 2);
    cr_assert_eq(((struct my_struct *)vec_at(vec2, 1))->a, 3);
    cr_assert_eq(((struct my_struct *)vec_at(vec2, 1))->b, 4);
    cr_assert_eq(((struct my_struct *)vec_at(vec2, 2))->a, 5);
    cr_assert_eq(((struct my_struct *)vec_at(vec2, 2))->b, 6);
    vec_delete(vec);
    vec_delete(vec2);
}
