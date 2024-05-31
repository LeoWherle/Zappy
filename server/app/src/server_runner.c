/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** server_runner
*/

#include "common.h"
#include "serrorh.h"
#include "server.h"
#include "trantor.h"
#include "vector.h"
#include <bits/types/sigset_t.h>
#include <bits/types/struct_timeval.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

static sig_atomic_t global_running_state(bool set, bool value)
{
    static sig_atomic_t stop = false;

    if (set) {
        stop = value;
    }
    return stop;
}

static void fdset_append_client(client_t *client, serv_context_t *context)
{
    if (client->sd > 0) {
        FD_SET(client->sd, &context->readfds);
        if (client->write_buf.nmemb > 0) {
            FD_SET(client->sd, &context->writefds);
        }
        if (client->sd > context->max_sd) {
            context->max_sd = client->sd;
        }
    }
}

static void fdset_append_clients(server_t *server, serv_context_t *context)
{
    vec_foreach_arg(
        &server->clients, (for_fn_arg_t) fdset_append_client, context);
}

static void server_select(server_t *server, serv_context_t *context)
{
    struct timespec timeout = {0};

    timeout.tv_nsec = 2 * 1e7;
    FD_ZERO(&context->readfds);
    FD_ZERO(&context->writefds);
    FD_SET(server->listen_sd, &context->readfds);
    FD_SET(STDIN_FILENO, &context->readfds);
    if (server->command.write_buf.nmemb > 0) {
        FD_SET(STDOUT_FILENO, &context->writefds);
    }
    context->max_sd = server->listen_sd;
    fdset_append_clients(server, context);
    context->nready = pselect(context->max_sd + 1, &context->readfds,
        &context->writefds, NULL, &timeout, &context->mask);
    if (context->nready < 0 && errno != EINTR) {
        LOG_ERROR("select failed");
    }
}

static void server_handle_event(server_t *server, serv_context_t *context)
{
    if (FD_ISSET(server->listen_sd, &context->readfds)) {
        context->nready--;
        server_accept(server);
    }
    handle_command(server, context);
    handle_clients(server, context);
}

static void sigint_handler(int sig)
{
    (void) sig;
    LOG_DEBUG("Caught SIGINT, shutting down");
    global_running_state(true, true);
}

static int init_signal_handling(serv_context_t *context)
{
    sigset_t blockset = {0};
    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = 0,
    };

    if (sigemptyset(&blockset) < 0)
        return 1;
    if (sigaddset(&blockset, SIGINT) < 0)
        return 1;
    if (sigprocmask(SIG_BLOCK, &blockset, NULL) < 0)
        return 1;
    if (sigemptyset(&sa.sa_mask) < 0)
        return 1;
    if (sigaction(SIGINT, &sa, NULL) < 0)
        return 1;
    if (sigemptyset(&context->mask) < 0)
        return 1;
    return 0;
}

static void server_run_step(
    server_t *server, struct timespec *now, serv_context_t *context)
{
    struct timespec next;
    double delta = 0.0;

    server_select(server, context);
    if (global_running_state(false, 0)) {
        context->running = false;
        return;
    }
    server_handle_event(server, context);
    clock_gettime(CLOCK_MONOTONIC, &next);
    delta = (next.tv_sec - now->tv_sec)
        + (next.tv_nsec - now->tv_nsec) / 1e9;
    if (delta < 0.1)
        return;
    context->running = trantor_time_pass(&server->trantor, delta);
    *now = next;
}

void server_run(server_t *server)
{
    struct timespec now;
    serv_context_t context = {.max_sd = server->listen_sd, .running = true};

    srand(server->trantor.params.seed);
    if (init_signal_handling(&context))
        LOG_ERROR("Failed to initialize signal handling");
    clock_gettime(CLOCK_MONOTONIC, &now);
    init_trantor(&server->trantor);
    while (context.running)
        server_run_step(server, &now, &context);
}
