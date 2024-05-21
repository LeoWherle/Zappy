/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_append
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_append, test_vec_append)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vector_t *vec2 = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    vec_push_int(vec2, 4);
    vec_push_int(vec2, 5);
    vec_push_int(vec2, 6);
    if (vec_append(vec, vec2) != BUF_OK) {
        cr_assert_eq(false, true);
    }
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    cr_assert_eq(*vec_at_int(vec, 1), 2);
    cr_assert_eq(*vec_at_int(vec, 2), 3);
    cr_assert_eq(*vec_at_int(vec, 3), 4);
    cr_assert_eq(*vec_at_int(vec, 4), 5);
    cr_assert_eq(*vec_at_int(vec, 5), 6);
    cr_assert_eq(vec->nmemb, 6);
    cr_assert_eq(vec2->nmemb, 0);
    vec_delete(vec);
    vec_delete(vec2);
}

Test(vec_append, test_vec_append_big)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vector_t *vec2 = vec_new(sizeof(int), NULL, NULL);
    int i = 0;

    for (; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    for (; i < 2000; i++) {
        if (vec_push_int(vec2, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    cr_assert_eq(vec->nmemb, 1000);
    cr_assert_eq(vec2->nmemb, 1000);
    if (vec_append(vec, vec2) != BUF_OK) {
        cr_assert_eq(false, true);
    }
    for (i = 0; i < 2000; i++) {
        cr_assert_eq(*vec_at_int(vec, i), i);
    }
    cr_assert_eq(vec->nmemb, 2000);
    cr_assert_eq(vec2->nmemb, 0);
    vec_delete(vec);
    vec_delete(vec2);
}
