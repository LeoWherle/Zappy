/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** handle_client
*/

#include "serrorh.h"
#include "server.h"
#include "vector.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static void client_read(client_t *client, server_t *server)
{
    ssize_t red = 0;

    (void) server;
    if (vec_reserve(&client->read_buf, BUFFER_SIZE)) {
        LOG_WARN("Failed to reserve space in read buffer");
    }
    red = read(client->sd, client->read_buf.items + client->read_buf.nmemb,
        client->read_buf.capacity - client->read_buf.nmemb);
    if (red < 0) {
        LOG_ERROR("Failed to read from client");
        return;
    }
    if (red == 0) {
        LOG_INFO("Client disconnected");
        client->delete = true;
        return;
    }
    client->read_buf.nmemb += red;
    LOG_TRACE("Read %ld bytes from client with fd: %d", red, client->sd);
}

// Write the client's write buffer to the client's socket
static void client_write(client_t *client)
{
    ssize_t written = 0;

    if (client->write_buf.nmemb == 0) {
        return;
    }
    written =
        write(client->sd, client->write_buf.items, client->write_buf.nmemb);
    if (written < 0) {
        LOG_ERROR("Failed to write to client");
        return;
    }
    if (vec_erase(&client->write_buf, 0, written) != BUF_OK) {
        LOG_ERROR("Failed to erase written bytes from write buffer");
        return;
    }
    LOG_TRACE("Wrote %ld bytes to client with fd: %d", written, client->sd);
}

static void client_consume_read_buffer(client_t *client, size_t consumed)
{
    if (consumed > 0) {
        if (vec_erase(&client->read_buf, 0, consumed) != BUF_OK) {
            LOG_ERROR("Failed to erase consumed bytes from read buffer");
        }
    }
}

static void client_handle_event(
    client_t *client, server_t *server, serv_context_t *context)
{
    size_t consumed = 0;

    if (FD_ISSET(client->sd, &context->readfds)) {
        context->nready--;
        client_read(client, server);
        consumed = client_execute(client, server);
        client_consume_read_buffer(client, consumed);
    }
    if (FD_ISSET(client->sd, &context->writefds)) {
        context->nready--;
        client_write(client);
    }
}

static bool client_should_delete(client_t *client)
{
    return client->delete;
}

static void client_cleanup(server_t *server)
{
    vec_remove_if(&server->clients, (vec_pred_t) client_should_delete);
}

void handle_clients(server_t *server, serv_context_t *context)
{
    size_t i = 0;
    vector_t *clients = NULL;

    if (server == NULL || context == NULL)
        return;
    clients = &server->clients;
    for (; i < clients->nmemb || context->nready < 0; i++) {
        client_handle_event(VEC_AT(clients, i), server, context);
    }
    client_cleanup(server);
}
