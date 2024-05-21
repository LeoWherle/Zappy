/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_insert
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_at, test_vec_insert)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    vec_insert_int(vec, 4, 1);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    cr_assert_eq(*vec_at_int(vec, 1), 4);
    cr_assert_eq(*vec_at_int(vec, 2), 2);
    cr_assert_eq(*vec_at_int(vec, 3), 3);
    vec_delete(vec);
}

Test(vec_at, big_test_vec_insert)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    if (vec_insert_int(vec, 1000, 500) != BUF_OK) {
        cr_assert_eq(false, true);
    }

    for (int i = 0; i < 500; i++) {
        cr_assert_eq(*vec_at_int(vec, i), i);
    }
    cr_assert_eq(*vec_at_int(vec, 500), 1000);
    for (int i = 501; i < 1000; i++) {
        cr_assert_eq(*vec_at_int(vec, i), i - 1);
    }
    vec_delete(vec);
}

Test(vec_at, test_invalid_index)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    cr_assert(vec_insert_int(vec, 4, 4) != BUF_OK);
    cr_assert(vec_insert_int(vec, 4, 3) == BUF_OK);
    vec_delete(vec);
}

Test(vec_insert, char)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    vec_push_char(vec, 'a');
    vec_push_char(vec, 'b');
    vec_push_char(vec, 'c');
    vec_insert_char(vec, 'd', 1);
    cr_assert_eq(*vec_at_char(vec, 0), 'a');
    cr_assert_eq(*vec_at_char(vec, 1), 'd');
    cr_assert_eq(*vec_at_char(vec, 2), 'b');
    cr_assert_eq(*vec_at_char(vec, 3), 'c');
    vec_delete(vec);
}

Test(vec_insert, float)
{
    vector_t *vec = vec_new(sizeof(float), NULL, NULL);

    vec_push_float(vec, 1.1f);
    vec_push_float(vec, 2.2f);
    vec_push_float(vec, 3.3f);
    vec_insert_float(vec, 4.4f, 1);
    cr_assert_eq(*vec_at_float(vec, 0), 1.1f);
    cr_assert_eq(*vec_at_float(vec, 1), 4.4f);
    cr_assert_eq(*vec_at_float(vec, 2), 2.2f);
    cr_assert_eq(*vec_at_float(vec, 3), 3.3f);
    vec_delete(vec);
}

Test(vec_insert, double)
{
    vector_t *vec = vec_new(sizeof(double), NULL, NULL);

    vec_push_double(vec, 1.1);
    vec_push_double(vec, 2.2);
    vec_push_double(vec, 3.3);
    vec_insert_double(vec, 4.4, 1);
    cr_assert_eq(*vec_at_double(vec, 0), 1.1);
    cr_assert_eq(*vec_at_double(vec, 1), 4.4);
    cr_assert_eq(*vec_at_double(vec, 2), 2.2);
    cr_assert_eq(*vec_at_double(vec, 3), 3.3);
    vec_delete(vec);
}

Test(vec_insert, invalid_index)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    cr_assert(vec_insert_int(vec, 4, 4) != BUF_OK);
    cr_assert(vec_insert_int(vec, 4, 3) == BUF_OK);
    vec_delete(vec);
}

Test(vec_insert, invalid_index_char)
{
    vector_t *vec = vec_new(sizeof(char), NULL, NULL);

    vec_push_char(vec, 'a');
    vec_push_char(vec, 'b');
    vec_push_char(vec, 'c');
    cr_assert(vec_insert_char(vec, 'd', 4) != BUF_OK);
    cr_assert(vec_insert_char(vec, 'd', 3) == BUF_OK);
    vec_delete(vec);
}

Test(vec_insert, invalid_index_float)
{
    vector_t *vec = vec_new(sizeof(float), NULL, NULL);

    vec_push_float(vec, 1.1f);
    vec_push_float(vec, 2.2f);
    vec_push_float(vec, 3.3f);
    cr_assert(vec_insert_float(vec, 4.4f, 4) != BUF_OK);
    cr_assert(vec_insert_float(vec, 4.4f, 3) == BUF_OK);
    vec_delete(vec);
}

Test(vec_insert, invalid_index_double)
{
    vector_t *vec = vec_new(sizeof(double), NULL, NULL);

    vec_push_double(vec, 1.1);
    vec_push_double(vec, 2.2);
    vec_push_double(vec, 3.3);
    cr_assert(vec_insert_double(vec, 4.4, 4) != BUF_OK);
    cr_assert(vec_insert_double(vec, 4.4, 3) == BUF_OK);
    vec_delete(vec);
}
