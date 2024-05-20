/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_at
*/

#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include "vector.h"

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_at, test_vec_at)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    cr_assert_eq(*vec_at_int(vec, 1), 2);
    cr_assert_eq(*vec_at_int(vec, 2), 3);
    vec_delete(vec);
}

Test(vec_at, test_vec_at_char)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    vec_push_char(vec, 'a');
    vec_push_char(vec, 'b');
    vec_push_char(vec, 'c');
    cr_assert_eq(*vec_at_char(vec, 0), 'a');
    cr_assert_eq(*vec_at_char(vec, 1), 'b');
    cr_assert_eq(*vec_at_char(vec, 2), 'c');
    vec_delete(vec);
}

Test(vec_at, test_vec_at_float)
{
    vector_t *vec = vec_new(sizeof(float), NULL, NULL);

    vec_push_float(vec, 1.1f);
    vec_push_float(vec, 2.2f);
    vec_push_float(vec, 3.3f);
    cr_assert_eq(*vec_at_float(vec, 0), 1.1f);
    cr_assert_eq(*vec_at_float(vec, 1), 2.2f);
    cr_assert_eq(*vec_at_float(vec, 2), 3.3f);
    vec_delete(vec);
}

Test(vec_at, test_vec_at_double)
{
    vector_t *vec = vec_new(sizeof(double), NULL, NULL);

    vec_push_double(vec, 1.1);
    vec_push_double(vec, 2.2);
    vec_push_double(vec, 3.3);
    cr_assert_eq(*vec_at_double(vec, 0), 1.1);
    cr_assert_eq(*vec_at_double(vec, 1), 2.2);
    cr_assert_eq(*vec_at_double(vec, 2), 3.3);
    vec_delete(vec);
}

Test(vec_at, invalid_index)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    cr_assert_null(vec_at_int(vec, 3));
    cr_assert_null(vec_at_int(vec, -1));
    vec_delete(vec);
}
