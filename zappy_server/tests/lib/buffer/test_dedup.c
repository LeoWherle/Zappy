/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_dedup
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

bool int_eq(const void *a, const void *b)
{
    return (*(int *)a == *(int *)b);
}

Test(dedup, test_dedup)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 2);
    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    vec_push_int(vec, 3);
    vec_push_int(vec, 3);
    vec_push_int(vec, 4);
    vec_push_int(vec, 4);

    vec_dedup(vec, int_eq);

    cr_assert(vec->nmemb == 4, "vec->nmemb = %ld", vec->nmemb);
    cr_assert_eq(*vec_at_int(vec, 0), 2);
    cr_assert_eq(*vec_at_int(vec, 1), 1);
    cr_assert_eq(*vec_at_int(vec, 2), 3);
    cr_assert_eq(*vec_at_int(vec, 3), 4);
    vec_delete(vec);
}

Test(dedup, test_dedup_big)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    for (int i = 0; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    vec_dedup(vec, int_eq);

    cr_assert(vec->nmemb == 1000, "vec->nmemb = %ld", vec->nmemb);
    for (int i = 0; i < 1000; i++) {
        cr_assert_eq(*vec_at_int(vec, i), i);
    }
    vec_delete(vec);
}

Test(dedup, test_dedup_empty)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_dedup(vec, int_eq);

    cr_assert(vec->nmemb == 0, "vec->nmemb = %ld", vec->nmemb);
    vec_delete(vec);
}

Test(dedup, test_dedup_one)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_dedup(vec, int_eq);

    cr_assert(vec->nmemb == 1, "vec->nmemb = %ld", vec->nmemb);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    vec_delete(vec);
}

Test(dedup, test_dedup_two)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 1);
    vec_dedup(vec, int_eq);

    cr_assert(vec->nmemb == 1, "vec->nmemb = %ld", vec->nmemb);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    vec_delete(vec);
}

Test(dedup, test_dedup_three)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 1);
    vec_push_int(vec, 1);
    vec_dedup(vec, int_eq);

    cr_assert(vec->nmemb == 1, "vec->nmemb = %ld", vec->nmemb);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    vec_delete(vec);
}
