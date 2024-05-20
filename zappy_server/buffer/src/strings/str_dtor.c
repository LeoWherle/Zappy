/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** str_dtor
*/

#include "sstrings.h"

void str_dtor(void *str)
{
    str_delete(str);
}

void str_delete(string_t *str)
{
    vec_delete((vector_t *) str);
}

void str_clear(string_t *str)
{
    vec_clear((vector_t *) str);
}

void str_reset(string_t *str)
{
    vec_reset((vector_t *) str);
}
