/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** handle_command
*/

#include "serrorh.h"
#include "server.h"
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>

static void read_command(serv_command_t *cmd, serv_context_t *context)
{
    ssize_t red = 0;

    if (vec_reserve(str_to_vec(&cmd->read_buf), BUFFER_SIZE)) {
        LOG_WARN("Failed to reserve space in read buffer");
    }
    red = read(STDIN_FILENO, cmd->read_buf.items + cmd->read_buf.nmemb,
        cmd->read_buf.capacity - cmd->read_buf.nmemb);
    if (red < 0) {
        LOG_ERROR("Failed to read from STDIN");
        return;
    }
    if (red == 0) {
        LOG_DEBUG("Shutting down server, received EOF from stdin");
        context->running = false;
    }
    cmd->read_buf.nmemb += red;
}

static void command_write(serv_command_t *cmd)
{
    ssize_t written = 0;

    if (cmd->write_buf.nmemb == 0) {
        return;
    }
    written = write(STDOUT_FILENO, cmd->write_buf.items, cmd->write_buf.nmemb);
    if (written < 0) {
        LOG_ERROR("Failed to write to STDOUT");
        return;
    }
    if (str_erase(&cmd->write_buf, 0, written) != BUF_OK) {
        LOG_ERROR("Failed to erase written bytes from write buffer");
        return;
    }
}

static void command_consume_buffer(serv_command_t *client, size_t consumed)
{
    if (consumed > 0) {
        if (str_erase(&client->read_buf, 0, consumed) != BUF_OK) {
            LOG_ERROR("Failed to erase consumed bytes from read buffer");
        }
    }
}

void handle_command(server_t *server, serv_context_t *context)
{
    size_t consumed = 0;

    if (FD_ISSET(STDIN_FILENO, &context->readfds)) {
        context->nready--;
        read_command(&server->command, context);
        consumed = command_execute(server, context);
        command_consume_buffer(&server->command, consumed);
    }
    if (FD_ISSET(STDOUT_FILENO, &context->writefds)) {
        context->nready--;
        command_write(&server->command);
    }
}
