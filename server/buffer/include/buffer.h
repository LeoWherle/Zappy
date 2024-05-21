/*
** EPITECH PROJECT, 2024
** c_project [WSL: Ubuntu]
** File description:
** buffer
*/

#pragma once

typedef enum buf_error_e {
    BUF_OK = 0,
    BUF_ALLOC,
    BUF_INDEX,
    BUF_EMPTY,
    BUF_CAPACITY,
    BUF_SIZE,
    BUF_NULLPTR,
    BUF_INVALID,
} buf_error_t;
