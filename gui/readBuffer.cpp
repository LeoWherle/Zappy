/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** readBuffer
*/

#pragma once

#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <vector>
#include "readBuffer.hpp"


readBuffer::readBuffer() : _pos(0), _filled(0)
{
}

readBuffer::readBuffer(uint32_t size) : _pos(0), _filled(0)
{
    _buffer.resize(size);
}

auto readBuffer::capacity() const -> uint32_t
{
    return _buffer.size();
}

auto readBuffer::buffer() const -> std::vector<uint8_t>
{
    return std::vector<uint8_t>(_buffer.begin() + _pos, _buffer.begin() + _filled);
}

auto readBuffer::fill_buffer(std::function<ssize_t(uint8_t *, uint32_t)> reader) -> void
{
    if (_filled == _buffer.size()) {
        return;
    }
    // assure there is at least 4096 bytes available
    if (_filled + _DEFAULT_SIZE > _buffer.size()) {
        _buffer.resize(_filled + _DEFAULT_SIZE);
    }
    ssize_t read = reader(_buffer.data() + _filled, _buffer.size() - _filled);
    if (read == -1) {
        throw ReadError("Error reading");
    } else if (read == 0 && _buffer.begin() + _filled == _buffer.end()) {
        throw ConnectionClosed("EOF");
    }
    _filled += read;
}
