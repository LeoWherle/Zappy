/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** string utils
*/

#include "trantor/string_utils.h"
#include "serrorh.h"

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void talk(string_t *buf, const char *msg)
{
    if (str_push_cstr(buf, msg) != BUF_OK)
        LOG_ERROR("Error while pushing message:\n%s\n", msg);
}

void pop_line(string_t *buf)
{
    const char *nline = strchr(buf->items, '\n');

    if (nline == NULL)
        return;
    if (str_erase(buf, 0, nline - (char *)buf->items + 1) != BUF_OK)
        LOG_ERROR("Error while popping line\n");
}

void talkf(string_t *buf, const char *fmt, ...)
{
    va_list args;
    int len = 0;
    char *str = NULL;

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    if (len == -1)
        return;
    if (vec_reserve(str_to_vec(buf), len + 1) != BUF_OK)
        return;
    str = buf->items + buf->nmemb;
    vsprintf(str, fmt, args);
    va_end(args);
    free(str);
}

char *aprintf(const char *fmt, ...)
{
    va_list args;
    int len = 0;
    char *str = NULL;

    va_start(args, fmt);
    len = vsnprintf(NULL, 0, fmt, args);
    if (len == -1)
        return NULL;
    str = malloc(sizeof(char) * (len + 1));
    vsprintf(str, fmt, args);
    va_end(args);
    return str;
}
