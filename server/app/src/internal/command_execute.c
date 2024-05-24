/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** command_execute
*/

#include "serrorh.h"
#include "server.h"
#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static const cmd_t commands[] = {
    {"exit", command_exit},
    {"ping", command_ping},
    {"help", command_help},
    {"log", command_log},
};

void command_help(server_t *server, serv_context_t *context, vector_t *args)
{
    char h[] = "Available commands:\n";

    (void) context;
    (void) args;
    if (str_push_bytes(&server->command.write_buf, h, sizeof(h))) {
        LOG_ERROR("Failed to push response to write buffer");
    }
    for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        if (str_push_bytes(&server->command.write_buf, commands[i].cmd,
                strlen(commands[i].cmd))) {
            LOG_ERROR("Failed to push response to write buffer");
        }
        if (str_push_char(&server->command.write_buf, '\n')) {
            LOG_ERROR("Failed to push response to write buffer");
        }
    }
}

static ssize_t strchrln(char *str, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '\n') {
            return i;
        }
    }
    return -1;
}

// split the cmd and put the pointers to the args vector
static void tokenize_command(char *cmd, size_t len, vector_t *args)
{
    char *start = cmd;
    char *end = cmd;
    buf_error_t err = BUF_OK;

    for (size_t j = 0; j <= len; j++) {
        if (cmd[j] == ' ' || cmd[j] == '\n' || cmd[j] == '\0') {
            end = cmd + j;
            err = vec_push(args, &start);
            *end = '\0';
            start = cmd + j + 1;
        }
        if (err != BUF_OK) {
            LOG_ERROR("Failed to push response to write buffer");
        }
    }
}

static size_t command_exec(
    server_t *server, serv_context_t *context, char *cmd, size_t len)
{
    vector_t args = {0};

    cmd[len] = '\0';
    if (vec_init(&args, sizeof(char *), NULL, NULL) != BUF_OK) {
        LOG_ERROR("Failed to create args vector");
        return len + 1;
    }
    tokenize_command(cmd, len, &args);
    for (size_t i = 0; i < sizeof(commands) / sizeof(*commands); i++) {
        if (!strncmp(cmd, commands[i].cmd, len)) {
            commands[i].func(server, context, &args);
            vec_reset(&args);
            return len + 1;
        }
    }
    LOG_ERROR("Unknown command, wtf is this");
    vec_reset(&args);
    return len + 1;
}

size_t command_execute(server_t *server, serv_context_t *context)
{
    size_t consumed = 0;
    char *cmd = server->command.read_buf.items;
    ssize_t len = strchrln(cmd, server->command.read_buf.nmemb);

    if (len == 0) {
        return 1;
    }
    if (len > 0) {
        consumed = command_exec(server, context, cmd, len);
    }
    return consumed;
}
