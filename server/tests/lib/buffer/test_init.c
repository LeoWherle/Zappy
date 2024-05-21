/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** test_init
*/

#include <criterion/criterion.h>
#include "vector.h"
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
Test(vector, vec_init)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);

    cr_assert_not_null(vec);
    cr_assert_eq(vec->item_size, sizeof(int));
    cr_assert_eq(vec->nmemb, 0);
    cr_assert_eq(vec->capacity, VEC_INIT_CAPACITY);
    cr_assert_not_null(vec->items);
    vec_delete(vec);
}

Test(vector, vec_reserve)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    buf_error_t err = 0;
    cr_assert_eq(vec->capacity, VEC_INIT_CAPACITY);
    cr_assert_eq(err, BUF_OK);
    vec_delete(vec);
}

Test(vector, vec_with_capacity)
{
    vector_t *vec = vec_with_capacity(12, sizeof(int), NULL, NULL);

    cr_assert_not_null(vec);
    cr_assert_eq(vec->item_size, sizeof(int));
    cr_assert_eq(vec->nmemb, 0);
    cr_assert_not_null(vec->items);
    vec_delete(vec);

    vec = vec_with_capacity(0, sizeof(int), NULL, NULL);
    cr_assert_not_null(vec);
    cr_assert_eq(vec->item_size, sizeof(int));
    cr_assert_eq(vec->nmemb, 0);
    cr_assert_eq(vec->capacity, VEC_INIT_CAPACITY);
    vec_delete(vec);
}

Test(vector, vec_push)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    int value = 42;
    buf_error_t err = vec_push(vec, &value);

    cr_assert_eq(err, BUF_OK);
    cr_assert_eq(vec->nmemb, 1);
    cr_assert_eq(*(int *)vec->items, 42);
    vec_delete(vec);
}

Test(vector, vec_pop)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    buf_error_t err = vec_pop(vec);

    cr_assert_eq(err, BUF_OK);
    cr_assert_eq(vec->nmemb, 0);
    vec_delete(vec);
}

Test(vector, vec_delete_at)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    buf_error_t err = vec_delete_at(vec, 1);

    cr_assert_eq(err, BUF_OK);
    cr_assert_eq(vec->nmemb, 2);
    cr_assert_eq(*(int *)vec->items, 42);
    cr_assert_eq(*((int *)vec->items + 1), 44);
    vec_delete(vec);
}

Test(vector, vec_remove)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    int *value = vec_remove(vec, 1);

    cr_assert_not_null(value);
    cr_assert_eq(*value, 43);
    cr_assert_eq(vec->nmemb, 2);
    cr_assert_eq(*(int *)vec->items, 42);
    cr_assert_eq(*((int *)vec->items + 1), 44);
    free(value);
    vec_delete(vec);
}

Test(vector, vec_swap_remove)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    int *value = NULL;
    
    value = vec_swap_remove(vec, 1);
    int value2 = *(int *)value;

    cr_assert_not_null(value);
    cr_assert_eq(value2, 43);
    cr_assert_eq(vec->nmemb, 2);
    cr_assert_eq(*vec_at_int(vec, 0), 42);
    cr_assert(*(int *)(vec->items + sizeof(int)) == 44, "Expected %d but got %d", 44, *(int *)(vec->items + sizeof(int)));

    free(value);
    vec_delete(vec);

    vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    value = vec_swap_remove(vec, 2);

    cr_assert_not_null(value);
    cr_assert_eq(*value, 44);
    cr_assert_eq(vec->nmemb, 2);
    cr_assert_eq(*(int *)vec->items, 42);
    cr_assert_eq(*((int *)vec->items + 1), 43);
    free(value);
    vec_delete(vec);
}

Test(vector, vec_at)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);

    cr_assert_eq(*(int *)vec_at(vec, 0), 42);
    cr_assert_eq(*(int *)vec_at(vec, 1), 43);
    cr_assert_eq(*(int *)vec_at(vec, 2), 44);
    cr_assert_null(vec_at(vec, 3));
    vec_delete(vec);
}


Test(vector, vec_clear)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vec_clear(vec);

    cr_assert_eq(vec->nmemb, 0);
    cr_assert_eq(*(int *)vec->items, 0);
    cr_assert_eq(*((int *)vec->items + 1), 0);
    cr_assert_eq(*((int *)vec->items + 2), 0);
    vec_delete(vec);
}

void *map_fn(const void *item)
{
    int *value = malloc(sizeof(int));

    if (value == NULL)
        return NULL;
    *value = *(int *)item * 2;
    return value;
}

Test(vector, vec_map)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vector_t *new_vec = vec_map(vec, &map_fn);

    cr_assert_not_null(new_vec);
    cr_assert_eq(new_vec->nmemb, 3);
    cr_assert_eq(*(int *)new_vec->items, 84);
    cr_assert_eq(*((int *)new_vec->items + 1), 86);
    cr_assert_eq(*((int *)new_vec->items + 2), 88);
    vec_delete(vec);
    vec_delete(new_vec);
}

void *map_fn_arg(const void *item, void *arg)
{
    int *value = malloc(sizeof(int));

    if (value == NULL)
        return NULL;
    *value = *(int *)item * (int)arg;
    return value;
}

Test(vector, vec_map_arg)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vector_t *new_vec = vec_map_arg(vec, &map_fn_arg, (void *)2);

    cr_assert_not_null(new_vec);
    cr_assert_eq(new_vec->nmemb, 3);
    cr_assert_eq(*(int *)new_vec->items, 84);
    cr_assert_eq(*((int *)new_vec->items + 1), 86);
    cr_assert_eq(*((int *)new_vec->items + 2), 88);
    vec_delete(vec);
    vec_delete(new_vec);
}

bool filter_fn(const void *item)
{
    return *(int *)item % 2 == 0;
}

Test(vector, vec_filter)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vector_t *new_vec = vec_filter(vec, &filter_fn);

    cr_assert_not_null(new_vec);
    cr_assert_eq(new_vec->nmemb, 2);
    cr_assert_eq(*(int *)new_vec->items, 42);
    cr_assert_eq(*((int *)new_vec->items + 1), 44);
    vec_delete(vec);
    vec_delete(new_vec);
}

bool find_fn(const void *item)
{
    return *(int *)item == 43;
}

Test(vector, vec_find)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    int *value = vec_find(vec, &find_fn);

    cr_assert_not_null(value);
    cr_assert_eq(*value, 43);
    vec_delete(vec);
}

bool find_fn_arg(const void *item, void *arg)
{
    return *(int *)item == (int)arg;
}

Test(vector, vec_find_arg)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    int *value = vec_find_arg(vec, &find_fn_arg, (void *)43);

    cr_assert_not_null(value);
    cr_assert_eq(*value, 43);
    vec_delete(vec);
}

bool count_fn(const void *item)
{
    return *(int *)item % 2 == 0;
}

Test(vector, vec_count)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    size_t count = vec_count(vec, &count_fn);

    cr_assert_eq(count, 2);
    vec_delete(vec);
}

void foreach_fn(void *item)
{
    *(int *)item *= 2;
}

Test(vector, vec_foreach)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vec_foreach(vec, &foreach_fn);

    cr_assert_eq(*(int *)vec->items, 84);
    cr_assert_eq(*((int *)vec->items + 1), 86);
    cr_assert_eq(*((int *)vec->items + 2), 88);
    vec_delete(vec);
}

void foreach_fn_arg(void *item, void *arg)
{
    *(int *)item *= (int)arg;
}

Test(vector, vec_foreach_arg)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vec_foreach_arg(vec, &foreach_fn_arg, (void *)2);

    cr_assert_eq(*(int *)vec->items, 84);
    cr_assert_eq(*((int *)vec->items + 1), 86);
    cr_assert_eq(*((int *)vec->items + 2), 88);
    vec_delete(vec);
}

Test(vector, vec_retain_if)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vec_retain_if(vec, &filter_fn);

    cr_assert_eq(vec->nmemb, 2);
    cr_assert_eq(*(int *)vec->items, 42);
    cr_assert_eq(*((int *)vec->items + 1), 44);
    vec_delete(vec);
}

Test(vector, vec_delete)
{
    vector_t *vec = vec_new(sizeof(int), NULL, NULL);
    vec_push_int(vec, 42);
    vec_push_int(vec, 43);
    vec_push_int(vec, 44);
    vec_delete(vec);
    cr_assert(1);
}