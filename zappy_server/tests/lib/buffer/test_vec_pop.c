/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_pop
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_pop, test_vec_pop)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);

    cr_assert_eq(vec_pop_int(vec), BUF_OK);
    cr_assert_eq(vec_pop_int(vec), BUF_OK);
    cr_assert_eq(vec_pop_int(vec), BUF_OK);
    cr_assert_eq(vec_pop_int(vec), BUF_EMPTY);
    vec_delete(vec);
}

Test(vec_pop, test_vec_pop_big)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    for (int i = 999; i >= 0; i--) {
        cr_assert_eq(vec_pop_int(vec), BUF_OK);
    }
    cr_assert_eq(vec_pop_int(vec), BUF_EMPTY);
    vec_delete(vec);
}

Test(vec_pop_char, test_vec_pop_char)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    vec_push_char(vec, 'a');
    vec_push_char(vec, 'b');
    vec_push_char(vec, 'c');

    cr_assert_eq(vec_pop_char(vec), BUF_OK);
    cr_assert_eq(vec_pop_char(vec), BUF_OK);
    cr_assert_eq(vec_pop_char(vec), BUF_OK);
    cr_assert_eq(vec_pop_char(vec), BUF_EMPTY);
    vec_delete(vec);
}

Test(vec_pop_float, test_vec_pop_float)
{
    vector_t *vec = vec_new(sizeof(float), NULL, NULL);

    vec_push_float(vec, 1.1);
    vec_push_float(vec, 2.2);
    vec_push_float(vec, 3.3);

    cr_assert_eq(vec_pop_float(vec), BUF_OK);
    cr_assert_eq(vec_pop_float(vec), BUF_OK);
    cr_assert_eq(vec_pop_float(vec), BUF_OK);
    cr_assert_eq(vec_pop_float(vec), BUF_EMPTY);
    vec_delete(vec);
}

Test(vec_pop_double, test_vec_pop_double)
{
    vector_t *vec = vec_new(sizeof(double), NULL, NULL);

    vec_push_double(vec, 1.1);
    vec_push_double(vec, 2.2);
    vec_push_double(vec, 3.3);

    cr_assert_eq(vec_pop_double(vec), BUF_OK);
    cr_assert_eq(vec_pop_double(vec), BUF_OK);
    cr_assert_eq(vec_pop_double(vec), BUF_OK);
    cr_assert_eq(vec_pop_double(vec), BUF_EMPTY);
    vec_delete(vec);
}
