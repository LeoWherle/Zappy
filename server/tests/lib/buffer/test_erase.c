/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** test_erase
*/

#include "vector.h"
#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#pragma GCC diagnostic ignored "-Wunused-result"

Test(vec_erase, test_vec_erase)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);

    cr_assert_eq(vec_erase(vec, 1, 2), BUF_OK);
    cr_assert_eq(*vec_at_int(vec, 0), 1);
    cr_assert_eq(vec_erase(vec, 0, 1), BUF_OK);
    cr_assert_eq(*vec_at_int(vec, 0), 3);
    vec_delete(vec);
}

Test(vec_erase, test_vec_erase_null)
{
    vector_t *vec = NULL;

    cr_assert_eq(vec_erase(vec, 1, 2), BUF_NULLPTR);
}

Test(vec_erase, test_vec_erase_out_of_range)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    vec_push_int(vec, 1);
    vec_push_int(vec, 2);
    vec_push_int(vec, 3);

    cr_assert_eq(vec_erase(vec, 1, 4), BUF_NULLPTR);
    cr_assert_eq(vec_erase(vec, 4, 5), BUF_NULLPTR);
    vec_delete(vec);
}
