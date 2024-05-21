/*
** EPITECH PROJECT, 2024
** B-NWP-400-TLS-4-1-myteams-leo.wehrle [WSL: Ubuntu]
** File description:
** server
*/

#pragma once

#include "common.h"
#include "packets.h"
#include "vector.h"
#include <arpa/inet.h>
#include <bits/types/sigset_t.h>
#include <stdbool.h>
#include <stddef.h>
#include <sys/select.h>

#define MAX_CLIENTS 10

// Read = stdin, Write = stdout
// vector are char
typedef struct serv_command_s {
    vector_t read_buf;
    vector_t write_buf;
} serv_command_t;

// clients is a vector if client_t
typedef struct server_s {
    int listen_sd;
    int port;
    struct sockaddr_in addr;
    vector_t clients;
    serv_command_t command;
} server_t;

// both buffers are vectors of char
typedef struct client_s {
    bool delete;
    int sd;
    vector_t read_buf;
    vector_t write_buf;
    struct {
        struct {
            bool logged_in;
        };
    };
} client_t;

int server(server_t *server, const char *port_str);
int server_listen(server_t *server, uint16_t port, int max_clients);
server_t *server_create(void);
int server_socket_init(server_t *server);
void server_destroy(server_t *server);

void server_run(server_t *server);

void handle_clients(server_t *server, serv_context_t *context);
void handle_command(server_t *server, serv_context_t *context);
void server_accept(server_t *server);

/**
 * @brief execute the client's command from the read buffer or nothing if the
 * buffer is empty or the command is not complete
 *
 * @param client the client to execute the command from
 * @param server the server to execute the command on
 * @return size_t the number of bytes used from the read buffer to execute the
 * command, 0 if the command is not complete or the buffer is empty
 */
size_t client_execute(client_t *client, server_t *server);

size_t command_execute(server_t *server, serv_context_t *context);

void client_teardown(client_t *client);

[[deprecated("Use client->delete = true instead of client_remove()")]] void
client_remove(client_t *client, server_t *server);

/************************** COMMANDS ****************************************/

#define MAX_CMD_LENGTH 1024

// args is a vector of char *
typedef void (*input_cmd_t)(server_t *, serv_context_t *, vector_t *args);

typedef struct cmd_s {
    const char cmd[MAX_CMD_LENGTH + 1];
    input_cmd_t func;
} cmd_t;

void command_exit(server_t *server, serv_context_t *context, vector_t *args);
void command_help(server_t *server, serv_context_t *context, vector_t *args);
void command_ping(server_t *server, serv_context_t *context, vector_t *args);
void command_log(server_t *server, serv_context_t *context, vector_t *args);

/*************************** ACTIONS *****************************************/

typedef struct packet_s {
    char name[MAX_NAME_LENGTH + 1];
    bool (*handle)(server_t *server, client_t *client, client_packet_t *packet,
        pck_server_user_t *response);
} packet_t;

bool packet_login(server_t *server, client_t *client, client_packet_t *packet,
    pck_server_user_t *response);
bool packet_logout(server_t *server, client_t *client, client_packet_t *packet,
    pck_server_user_t *response);

bool packet_ping(server_t *server, client_t *client, client_packet_t *packet,
    pck_server_user_t *response);


// #define PACKET_SECTION_NAME     server_action

// #define PACKET_SECTION section(TOSTRING(PACKET_SECTION_NAME))

// #define PACKET_SECTION_START SECTION_DIFFER(start, PACKET_SECTION_NAME)
// #define PACKET_SECTION_STOP  SECTION_DIFFER(stop, PACKET_SECTION_NAME)

// extern actions_t PACKET_SECTION_START;
// extern actions_t PACKET_SECTION_STOP;
