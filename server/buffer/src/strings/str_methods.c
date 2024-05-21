/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_methods
*/

#include "sstrings.h"

const struct str_fn STR = {
    .new = str_new,
    .from_cstr = str_from_cstr,
    .delete = str_delete,
    .init = str_init,
    .reset = str_reset,
    .at = str_at,
    .push_char = str_push_char,
    .push_cstr = str_push_cstr,
    .push_str = str_push_str,
    .pop = str_pop,
    .erase = str_erase,
    .remove = str_remove,
    .insert = str_insert,
    .insert_bytes = str_insert_bytes,
    .insert_cstr = str_insert_cstr,
    .insert_str = str_insert_str,
    .as_vec = str_as_vec,
    .clear = str_clear,
};
