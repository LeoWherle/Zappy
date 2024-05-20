/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** vec_methods
*/

#include "vector.h"

const struct vec_fn VECTOR = {
    .new = vec_new,
    .delete = vec_delete,
    .reserve = vec_reserve,
    .init = vec_init,
    .reset = vec_reset,
    .with_capacity = vec_with_capacity,
    .swap_remove = vec_swap_remove,
    .insert = vec_insert,
    .remove = vec_remove,
    .delete_at = vec_delete_at,
    .erase = vec_erase,
    .remove_if = vec_remove_if,
    .retain_if = vec_retain_if,
    .push = vec_push,
    .pop = vec_pop,
    .append = vec_append,
    .append_array = vec_append_array,
    .clear = vec_clear,
    .is_empty = vec_is_empty,
    .split_off = vec_split_off,
    .extend_with = vec_extend_with,
    .dedup = vec_dedup,
    .clone = vec_clone,
    .print = vec_print,
    .display = vec_display,
    .sort = vec_sort,
    .foreach = vec_foreach,
    .foreach_arg = vec_foreach_arg,
    .find = vec_find,
    .find_arg = vec_find_arg,
    .count = vec_count,
    .filter = vec_filter,
    .map = vec_map,
    .map_arg = vec_map_arg,
    .at = vec_at,
    .indexof = vec_indexof,
};
