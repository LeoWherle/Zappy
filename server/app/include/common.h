/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** common
*/

#pragma once

#include <stdbool.h>
#include <sys/select.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

#define STRINGIFY(x) #x
#define TOSTRING(x)  STRINGIFY(x)

#define SECTION_DIFFER(pre, name) __ ## pre ## _ ## name
#define STRCONCAT(pre, name)      SECTION_DIFFER(pre, name)

#define SECTION_START(name) STRCONCAT(start, name)
#define SECTION_STOP(name)  STRCONCAT(stop, name)

typedef struct context_s serv_context_t;

typedef struct context_s {
    int max_sd;
    fd_set readfds;
    fd_set writefds;
    sigset_t mask;
    ssize_t nready;
    bool running;
} context_t;

void init_logging(const char *env_file);
