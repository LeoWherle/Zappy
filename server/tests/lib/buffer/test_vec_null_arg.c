/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_vec_null_arg
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_null_arg, test_vec_null_fun)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    cr_assert_not_null(vec);
    cr_assert_eq(vec_insert(NULL, NULL, 0) , BUF_NULLPTR);
    cr_assert_eq(vec_insert(vec, NULL, 0) , BUF_NULLPTR);
    cr_assert_eq(vec_delete_at(NULL, 0) , BUF_INDEX);
    cr_assert_eq(vec_remove(NULL, 0), NULL);
    cr_assert_eq(vec_swap_remove(NULL, 0), NULL);
    cr_assert_eq(vec_at(NULL, 0), NULL);
    cr_assert_eq(vec_reserve(NULL, 0), BUF_NULLPTR);
    cr_assert_eq(vec_clone(NULL), NULL);
    cr_assert_eq(vec_extend_with(NULL, NULL, 1), BUF_NULLPTR);
    cr_assert_eq(vec_extend_with(vec, NULL, 1), BUF_NULLPTR);
    vec_retain_if(NULL, NULL);
    vec_dedup(NULL, NULL);
    vec_sort(NULL, NULL);
    cr_assert(vec_map(NULL, NULL) == NULL);
    cr_assert(vec_map_arg(NULL, NULL, NULL) == NULL);
    cr_assert(vec_filter(NULL, NULL) == NULL);
    cr_assert_eq(vec_append(NULL, NULL), BUF_NULLPTR);
    cr_assert_eq(vec_split_off(NULL, 0), NULL);
    cr_assert_eq(vec_push(NULL, NULL), BUF_NULLPTR);
    cr_assert_eq(vec_pop(NULL), BUF_NULLPTR);
    cr_assert_eq(vec_find(NULL, NULL), NULL);
    cr_assert_eq(vec_find_arg(NULL, NULL, NULL), NULL);
    vec_delete(vec);
}