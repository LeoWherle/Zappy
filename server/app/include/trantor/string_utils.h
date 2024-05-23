/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** string utils
*/

#pragma once

#include "sstrings.h"

void talk(string_t *buf, const char *msg);

void pop_line(string_t *buf);

void talkf(string_t *buf, const char *fmt, ...);
