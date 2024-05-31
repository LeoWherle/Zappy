/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** assert
*/

#include "serrorh.h"

void expr_assert(int expr, const char *str)
{
    if (!expr) {
        log_msg(LG_ERROR, "Assertion failed: %s", str);
    }
}
