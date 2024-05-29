/*
** EPITECH PROJECT, 2023
** corewar [WSL: fedora]
** File description:
** cbuffer
*/

#ifndef SERRORH_H_
    #define SERRORH_H_

    #include <stdbool.h>
    #include <stdio.h>

#ifndef ERRORHANDLING_H_
    #define ERRORHANDLING_H_
    #define ERROR      84
    #define SUCCESS    0
    #define UNUSED     __attribute__((unused))
    #define DEPRECATED __attribute__((deprecated))
    #define WUR        __attribute__((warn_unused_result))
#endif /* !ERRORHANDLING_H_ */

#ifndef COLOR_H
    #define COLOR_H
    #define RESET   "\033[0m"
    #define BOLD    "\033[1m"
    #define BLACK   "\033[30m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"
    #define YELLOW  "\033[33m"
    #define BLUE    "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN    "\033[36m"
    #define WHITE   "\033[37m"
#endif /* COLOR_H */

/************* Using Header and Line Return *************/
    #define LOG_ERROR(...)     log_msg(LG_ERROR, __VA_ARGS__)
    #define LOG_WARN(...)      log_msg(LG_WARNING, __VA_ARGS__)
    #define LOG_INFO(...)      log_msg(LG_INFO, __VA_ARGS__)
    #define LOG_DEBUG(...)     log_msg(LG_DEBUG, __VA_ARGS__)
    #define LOG_TRACE(...)     log_msg(LG_TRACE, __VA_ARGS__)
    #define DEBUG_ASSERT(expr) expr_assert(expr, #expr)

    #define LOG_LEVEL_ENV    "LOG_LEVEL"
    #define LOG_FILE_ENV     "LOG_FILE"
    #define ENV_FILE_DEFAULT "server.env"

    #define MAX_LEVEL_STR_LEN 5

enum LogLevel {
    LG_ERROR = 0,
    LG_WARNING,
    LG_INFO,
    LG_DEBUG,
    LG_TRACE,
};

typedef struct {
    const char *color;
    const char name[MAX_LEVEL_STR_LEN + 1];
} loglevelmap_t;

void log_set_level(enum LogLevel level);
int load_env(const char *env_file);
void load_env_log_level(void);
void load_env_log_file(void);

FILE *global_log_file(bool set, FILE *value);

__attribute__((constructor)) void pre_load_env(void);
__attribute__((destructor)) void post_load_env(void);

int vflog_msg(FILE *file, enum LogLevel level, const char *__restrict format,
    va_list args);
__attribute__((__format__(printf, 2, 3))) int log_msg(
    enum LogLevel level, const char *__restrict format, ...);

/// if expr is false, print error message
void expr_assert(int expr, const char *fmt);

#endif /* !SERRORH_H_ */
