/*
** EPITECH PROJECT, 2024
** Template
** File description:
** Template
*/

#pragma once

#include <stdint.h>

#define MAX_NAME_LENGTH        32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_DESC_LEN          MAX_DESCRIPTION_LENGTH
#define MAX_BODY_LENGTH        512
#define MAX_UUID_LENGTH        36

#define MAX_INFO_DISPLAY 100

#define END_CMD "\r\n"

#define PACKED __attribute__((packed))

enum client_type_e {
    CLIENT_HELP,
    CLIENT_LOGIN,
    CLIENT_LOGOUT,
    CLIENT_PING,

    CLIENT_ENUM_COUNT,
};

// type is a value from client_type_e
typedef struct PACKED client_packet_s {
    uint8_t type;
    union {
        uint8_t login[MAX_NAME_LENGTH + 1];
    };
} client_packet_t;

/*********************************** SERVER **********************************/

enum server_type_e {
    SERVER_ERROR_INTERNAL,
    SERVER_OK,
    SERVER_EVENT_LOGGED_IN,
    SERVER_EVENT_LOGGED_OUT,
    SERVER_CONFIRM_LOGGED_OUT,
    SERVER_PONG,
    SERVER_ERROR_UNAUTHORIZED,
    SERVER_BAD_ARGS,

    SERVER_ENUM_COUNT,
};

/**
 * @brief Server packet to client
 * uint8_t for unautorized gives enum client_type_e as value
 */
typedef struct PACKED pck_server_user_s {
    uint8_t type;
    union {
        uint8_t value1;
    };
} pck_server_user_t;
