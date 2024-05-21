/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_remove
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_remove, test_vec_remove)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);

    cr_assert_eq(vec_remove_int(vec, 1), 2);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    cr_assert_eq(*vec_at_int(vec, 1), 3);
    cr_assert_eq(vec_remove_int(vec, 0), 1);
    cr_assert_eq(*vec_at_int(vec, 0), 3);
    cr_assert_eq(vec_remove_int(vec, 0), 3);
    cr_assert_eq(vec_remove_int(vec, 0), 0);
    vec_delete(vec);
}

Test(vec_remove, test_vec_remove_big)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    for (int i = 0; i < 1000; i++) {
        cr_assert_eq(vec_remove_int(vec, 0), i);
    }
    cr_assert_eq(vec_remove_int(vec, 0), 0);
    vec_delete(vec);
}

Test(vec_remove, test_invalid_index)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    cr_assert_eq(vec_remove_int(vec, 3), 0);
    cr_assert_eq(vec_remove_int(vec, 4), 0);
    cr_assert_eq(vec_remove_int(vec, 5), 0);
    vec_delete(vec);
}

Test(vec_remove, test_vec_remove_char)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    vec_push_char(vec, 'a');
    vec_push_char(vec, 'b');
    vec_push_char(vec, 'c');

    cr_assert_eq(vec_remove_char(vec, 1), 'b');
    cr_assert_eq(*vec_at_char(vec, 0), 'a');
    cr_assert_eq(*vec_at_char(vec, 1), 'c');
    cr_assert_eq(vec_remove_char(vec, 0), 'a');
    cr_assert_eq(*vec_at_char(vec, 0), 'c');
    cr_assert_eq(vec_remove_char(vec, 0), 'c');
    cr_assert_eq(vec_remove_char(vec, 0), '\0');
    vec_delete(vec);
}

Test(vec_remove, test_vec_remove_float)
{
    vector_t *vec = vec_new(sizeof(float), NULL, NULL);

    vec_push_float(vec, 1.1f);
    vec_push_float(vec, 2.2f);
    vec_push_float(vec, 3.3f);

    cr_assert_eq(vec_remove_float(vec, 1), 2.2f);
    cr_assert_eq(*vec_at_float(vec, 0), 1.1f);
    cr_assert_eq(*vec_at_float(vec, 1), 3.3f);
    cr_assert_eq(vec_remove_float(vec, 0), 1.1f);
    cr_assert_eq(*vec_at_float(vec, 0), 3.3f);
    cr_assert_eq(vec_remove_float(vec, 0), 3.3f);
    cr_assert_eq(vec_remove_float(vec, 0), 0.0f);
    vec_delete(vec);
}

Test(vec_remove, test_vec_remove_double)
{
    vector_t *vec = vec_new(sizeof(double), NULL, NULL);

    vec_push_double(vec, 1.1);
    vec_push_double(vec, 2.2);
    vec_push_double(vec, 3.3);

    cr_assert_eq(vec_remove_double(vec, 1), 2.2);
    cr_assert_eq(*vec_at_double(vec, 0), 1.1);
    cr_assert_eq(*vec_at_double(vec, 1), 3.3);
    cr_assert_eq(vec_remove_double(vec, 0), 1.1);
    cr_assert_eq(*vec_at_double(vec, 0), 3.3);
    cr_assert_eq(vec_remove_double(vec, 0), 3.3);
    cr_assert_eq(vec_remove_double(vec, 0), 0.0);
    vec_delete(vec);
}

Test(vec_remove, test_vec_remove_null)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    cr_assert_eq(vec_remove_int(NULL, 0), 0);
    cr_assert_eq(vec_remove_char(NULL, 0), 0);
    cr_assert_eq(vec_remove_float(NULL, 0), 0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_vec_swap_remove)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);

    cr_assert_eq(vec_swap_remove_int(vec, 0), 1);
    cr_assert_eq(*vec_at_int(vec, 0), 3);
    cr_assert_eq(*vec_at_int(vec, 1), 2);
    cr_assert_eq(vec_swap_remove_int(vec, 1), 2);
    cr_assert_eq(*vec_at_int(vec, 0), 3);
    cr_assert_eq(vec_swap_remove_int(vec, 0), 3);
    cr_assert_eq(vec_swap_remove_int(vec, 0), 0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_vec_swap_remove_big)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    for (int i = 999; i >= 0; i--) {
        cr_assert_eq(vec_swap_remove_int(vec, i), i);
    }
    cr_assert_eq(vec_swap_remove_int(vec, 0), 0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_invalid_index)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    cr_assert_eq(vec_swap_remove_int(vec, 3), 0);
    cr_assert_eq(vec_swap_remove_int(vec, 4), 0);
    cr_assert_eq(vec_swap_remove_int(vec, 5), 0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_vec_swap_remove_char)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    vec_push_char(vec, 'a');
    vec_push_char(vec, 'b');
    vec_push_char(vec, 'c');

    cr_assert_eq(vec_swap_remove_char(vec, 0), 'a');
    cr_assert_eq(*vec_at_char(vec, 0), 'c');
    cr_assert_eq(*vec_at_char(vec, 1), 'b');
    cr_assert_eq(vec_swap_remove_char(vec, 0), 'c');
    cr_assert_eq(*vec_at_char(vec, 0), 'b');
    cr_assert_eq(vec_swap_remove_char(vec, 0), 'b');
    cr_assert_eq(vec_swap_remove_char(vec, 0), 0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_vec_swap_remove_float)
{
    vector_t *vec = vec_new(sizeof(float), NULL, NULL);

    vec_push_float(vec, 1.1f);
    vec_push_float(vec, 2.2f);
    vec_push_float(vec, 3.3f);

    cr_assert_eq(vec_swap_remove_float(vec, 1), 2.2f);
    cr_assert_eq(*vec_at_float(vec, 0), 1.1f);
    cr_assert_eq(*vec_at_float(vec, 1), 3.3f);
    cr_assert_eq(vec_swap_remove_float(vec, 0), 1.1f);
    cr_assert_eq(*vec_at_float(vec, 0), 3.3f);
    cr_assert_eq(vec_swap_remove_float(vec, 0), 3.3f);
    cr_assert_eq(vec_swap_remove_float(vec, 0), 0.0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_vec_swap_remove_double)
{
    vector_t *vec = vec_new(sizeof(double), NULL, NULL);

    vec_push_double(vec, 1.1);
    vec_push_double(vec, 2.2);
    vec_push_double(vec, 3.3);

    cr_assert_eq(vec_swap_remove_double(vec, 1), 2.2);
    cr_assert_eq(*vec_at_double(vec, 0), 1.1);
    cr_assert_eq(*vec_at_double(vec, 1), 3.3);
    cr_assert_eq(vec_swap_remove_double(vec, 0), 1.1);
    cr_assert_eq(*vec_at_double(vec, 0), 3.3);
    cr_assert_eq(vec_swap_remove_double(vec, 0), 3.3);
    cr_assert_eq(vec_swap_remove_double(vec, 0), 0.0);
    vec_delete(vec);
}

Test(vec_swap_remove, test_vec_swap_remove_null)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    cr_assert_eq(vec_swap_remove_int(NULL, 0), 0);
    cr_assert_eq(vec_swap_remove_char(NULL, 0), 0);
    cr_assert_eq(vec_swap_remove_float(NULL, 0), 0);
    vec_delete(vec);
}