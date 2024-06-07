/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ReadBuffer
*/

#pragma once

#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>

namespace Buffer {
    class ReadBuffer {
    private:
        std::string _buffer;

        uint32_t _pos;
        uint32_t _filled;

        constexpr static uint32_t _DEFAULT_SIZE = 4096;

    public:
        // clang-format off
        class ConnectionClosed : public std::exception {
        private:
            const std::string _message;
        public:
            explicit ConnectionClosed(const std::string &message): _message(message) {}
            explicit ConnectionClosed(const char *const message): _message(message) {}
            virtual ~ConnectionClosed() noexcept { }
            const char *what() const noexcept override { return _message.c_str(); }
        };
        class ReadError : public std::exception {
        private:
            const std::string _message;
        public:
            explicit ReadError(const std::string &message): _message(message) {}
            explicit ReadError(const char *const message): _message(message) {}
            virtual ~ReadError() noexcept { }
            const char *what() const noexcept override { return _message.c_str(); }
        };
        // clang-format on

    public:
        ReadBuffer();
        ReadBuffer(uint32_t size);
        ~ReadBuffer() = default;

        auto capacity() const -> uint32_t;
        auto buffer() const -> std::string;

        inline auto available() const -> uint32_t { return _filled - _pos; };

        inline auto discard_buffer() -> void
        {
            _filled = 0;
            _pos = 0;
        }

        inline auto consume() -> void
        {
            _pos++;
            if (_pos >= _filled) {
                _pos = 0;
                _filled = 0;
            }
        }

        inline auto consume(uint32_t amount) -> void
        {
            _pos += amount;
            if (_pos >= _filled) {
                _pos = 0;
                _filled = 0;
            }
        }

        /**
         * @brief Example with a file descriptor:
         *
         * auto reader = [&fd](uint8_t *buffer, uint32_t size) -> uint32_t {
         *    return read(fd, buffer, size);
         * };
         */
        auto fill_buffer(std::function<ssize_t(char *, uint32_t)> reader) -> void;
    };
}