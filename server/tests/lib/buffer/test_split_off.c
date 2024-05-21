/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_split_off
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(split_off, test_split_off)
{
    vector_t *vec = NULL;
    vector_t *vec2 = NULL;

    vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    vec2 = vec_split_off(vec, 1);
    if (vec2 == NULL) {
        cr_assert_eq(false, true);
    }
    cr_assert_eq(vec->nmemb, 1);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    cr_assert_eq(vec2->nmemb, 2);
    cr_assert_eq(*vec_at_int(vec2, 0), 2);
    cr_assert_eq(*vec_at_int(vec2, 1), 3);
    vec_delete(vec);
    vec_delete(vec2);
}

Test(split_off, test_split_off_big)
{
    vector_t *vec = NULL;
    vector_t *vec2 = NULL;
    int i = 0;

    vec = vec_new(sizeof(int), NULL, NULL);
    for (; i < 1000; i++) {
        if (vec_push_int(vec, i) != BUF_OK) {
            cr_assert_eq(false, true);
        }
    }
    vec2 = vec_split_off(vec, 500);
    if (vec2 == NULL) {
        cr_assert_eq(false, true);
    }
    cr_assert_eq(vec->nmemb, 500);
    cr_assert_eq(vec2->nmemb, 500);
    for (i = 0; i < 500; i++) {
        cr_assert_eq(*vec_at_int(vec, i), i);
    }
    for (i = 0; i < 500; i++) {
        cr_assert_eq(*vec_at_int(vec2, i), i + 500);
    }
    vec_delete(vec);
    vec_delete(vec2);
}

Test(split_off, test_split_off_invalid_index)
{
    vector_t *vec = NULL;
    vector_t *vec2 = NULL;

    vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);
    vec2 = vec_split_off(vec, 4);
    cr_assert_eq(vec2, NULL);
    vec_delete(vec);
}
