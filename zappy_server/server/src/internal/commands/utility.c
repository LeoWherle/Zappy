/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** utility
*/

#include "packets.h"
#include "serrorh.h"
#include "server.h"
#include <string.h>

static const char *level_str[] = {"ERROR", "WARN", "INFO", "DEBUG", "TRACE"};

// change the log level
void command_log(server_t *server, serv_context_t *context, vector_t *args)
{
    char *item = NULL;

    (void) context;
    (void) server;
    LOG_INFO("Received log command");
    if (args->nmemb != 2) {
        LOG_ERROR("Invalid number of arguments: %lu", args->nmemb);
        return;
    }
    for (size_t i = 0; i < sizeof(level_str) / sizeof(*level_str); i++) {
        item = *(char **)vec_at(args, 1);
        if (strncasecmp(item, level_str[i], strlen(level_str[i])) == 0) {
            log_set_level(i);
            return;
        }
    }
}

void command_exit(server_t *server, serv_context_t *context, vector_t *args)
{
    (void) server;
    (void) args;
    context->running = false;
}

void command_ping(server_t *server, serv_context_t *context, vector_t *args)
{
    pck_server_user_t packet = {.type = SERVER_PONG};

    (void) context;
    (void) args;
    LOG_INFO("Received ping command");
    if (vec_append_array(
            &server->command.write_buf, &packet, sizeof(packet), 1)) {
        LOG_ERROR("Failed to push response to write buffer");
    }
}
