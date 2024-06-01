/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** give
*/

#pragma once

#include "common.h"
#include "server.h"
#include "vector.h"

typedef struct give_data_s {
    item_t type;
    quant_t amount;
} give_data_t;

typedef void (*value_cmd_t)(server_t *, vector_t *args);

/**
 * @brief give target -callback
 * @param target example: give "all" ...
 * @param target_short example: give "@a" ...
 * @param callback the function to execute depending on the target
 */
typedef struct give_cmd_s {
    const char target[MAX_CMD_LENGTH + 1];
    char target_short;
    value_cmd_t callback;
} give_cmd_t;

// give all | give @a
void give_all(server_t *serv, vector_t *args);

// give random | give @r
void give_random(server_t *serv, vector_t *args);

// give player <id> | give @p <id>
void give_player(server_t *serv, vector_t *args);

// give team <name> | give @t <name>
void give_team(server_t *serv, vector_t *args);
