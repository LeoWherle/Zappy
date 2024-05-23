/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** string utils
*/

#pragma once

#include "sstrings.h"

#define STRING_END(str) ((str)->items + (str)->nmemb)

void talk(string_t *buf, const char *msg);

void pop_line(string_t *buf);

void talkf(string_t *buf, const char *fmt, ...);

char *aprintf(const char *fmt, ...);

#define SAY_KO(buf) talk(buf, "ko\n")
#define SAY_OK(buf) talk(buf, "ok\n")
