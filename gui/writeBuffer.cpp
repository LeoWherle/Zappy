/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** writeBuffer
*/

#pragma once

#include <cstdint>
#include <string>
#include <unistd.h>
#include <vector>
#include "writeBuffer.hpp"

writeBuffer::writeBuffer(uint32_t size)
{
    _buffer.resize(size);
}

auto writeBuffer::size(void) -> std::size_t
{
    return _buffer.size();
}

auto writeBuffer::write_to_buffer(const void *data, uint32_t size) -> void
{
    _buffer.insert(_buffer.end(), (uint8_t *) data, (uint8_t *) data + size);
}

auto writeBuffer::write_to_buffer(const std::vector<uint8_t> &data) -> void
{
    _buffer.insert(_buffer.end(), data.begin(), data.end());
}

auto writeBuffer::write_to_buffer(const std::string &data) -> void
{
    _buffer.insert(_buffer.end(), data.begin(), data.end());
}

auto writeBuffer::_write(int fd) -> void
{
    auto ret = write(fd, _buffer.data(), _buffer.size());
    if (ret == -1) {
        throw WriteError("write() failed");
    }
    _buffer.clear();
}

auto writeBuffer::_write(int fd, const void *data, uint32_t size) -> void
{
    auto ret = write(fd, (uint8_t *) data, size);
    if (ret == -1) {
        throw WriteError("write() failed");
    }
    _buffer.erase(_buffer.begin(), _buffer.begin() + size);
}
