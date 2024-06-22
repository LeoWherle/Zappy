/*
** EPITECH PROJECT, 2024
** ntml-lib [WSL: fedora]
** File description:
** err_log
*/

#include "serrorh.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static loglevelmap_t level_map[] = {
    {RED, "ERROR"},
    {MAGENTA, "WARN"},
    {BLUE, "INFO"},
    {YELLOW, "DEBUG"},
    {GREEN, "TRACE"},
};

static enum LogLevel global_log_level(enum LogLevel level, bool set)
{
    static enum LogLevel global_verbose_mode = LG_INFO;

    if (set) {
        global_verbose_mode = level;
    }
    return global_verbose_mode;
}

void log_set_level(enum LogLevel level)
{
    (void) global_log_level(level, 1);
}

static bool is_colored(FILE *file)
{
    return (file == stderr || file == stdout) && global_log_color(0, 0);
}

int vflog_msg(FILE *file, enum LogLevel level, const char *__restrict format,
    va_list args)
{
    int ret = 0;

    if ((unsigned int) level <= global_log_level(0, 0)) {
        ret += fprintf(file, "[");
        if (is_colored(file))
            ret += fprintf(file, "%s" BOLD, level_map[level].color);
        ret += fprintf(file, "%s", level_map[level].name);
        if (is_colored(file))
            ret += fprintf(file, RESET);
        ret += fprintf(file, "] ");
        ret += vfprintf(file, format, args);
        if (format[strlen(format) - 1] != '\n')
            ret += fprintf(file, "\n");
        fflush(file);
    }
    return ret;
}

int log_msg(enum LogLevel level, const char *__restrict format, ...)
{
    FILE *file = NULL;
    va_list args;
    int ret = 0;

    file = global_log_file(false, NULL);
    if (file == NULL) {
        file = stderr;
    }
    va_start(args, format);
    ret = vflog_msg(file, level, format, args);
    va_end(args);
    return ret;
}

// Loads the log level from the environment variable LOG_LEVEL
void load_env_log_level(void)
{
    const char *log_level = NULL;

    log_level = getenv(LOG_LEVEL_ENV);
    if (log_level == NULL)
        return;
    for (size_t i = 0; i < sizeof(level_map) / sizeof(*level_map); i++) {
        if (strcasecmp(log_level, level_map[i].name) == 0) {
            log_set_level(i);
            return;
        }
    }
    log_msg(LG_WARNING, "Invalid log level: %s", log_level);
}
