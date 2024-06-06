/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WriteBuffer
*/

#pragma once

#include <cstdint>
#include <string>
#include <unistd.h>
#include <vector>

namespace Buffer {
    class WriteBuffer {
    private:    std::string _buffer;

    public:
        // clang-format off
        class WriteError : public std::exception {
        private:
            const std::string _message;
        public:
            explicit WriteError(const std::string &message): _message(message) {}
            explicit WriteError(const char *const message): _message(message) {}
            virtual ~WriteError() noexcept { }
            const char *what() const noexcept override { return _message.c_str(); }
        };
        // clang-format on

    public:
        WriteBuffer() = default;
        WriteBuffer(uint32_t size);
        ~WriteBuffer() = default;

        /***** Function to get info *****/

        auto size(void) -> std::size_t;

        /***** Functions to append new data *****/

        auto write_to_buffer(const void *data, uint32_t size) -> void;

        auto write_to_buffer(const std::string &data) -> void;


        /***** Functions write the buffer to ... *****/

        auto _write(int fd) -> void;

        auto _write(int fd, const void *data, uint32_t size) -> void;
    };
}