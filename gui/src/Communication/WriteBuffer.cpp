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
#include "WriteBuffer.hpp"

WriteBuffer::WriteBuffer(uint32_t size)
{
    _buffer.resize(size);
}

auto WriteBuffer::size(void) -> std::size_t
{
    return _buffer.size();
}

auto WriteBuffer::write_to_buffer(const void *data, uint32_t size) -> void
{
    _buffer.insert(_buffer.end(), (uint8_t *) data, (uint8_t *) data + size);
}

auto WriteBuffer::write_to_buffer(const std::vector<uint8_t> &data) -> void
{
    _buffer.insert(_buffer.end(), data.begin(), data.end());
}

auto WriteBuffer::write_to_buffer(const std::string &data) -> void
{
    _buffer.insert(_buffer.end(), data.begin(), data.end());
}

auto WriteBuffer::_write(int fd) -> void
{
    auto ret = write(fd, _buffer.data(), _buffer.size());
    if (ret == -1) {
        throw WriteError("write() failed");
    }
    _buffer.clear();
}

auto WriteBuffer::_write(int fd, const void *data, uint32_t size) -> void
{
    auto ret = write(fd, (uint8_t *) data, size);
    if (ret == -1) {
        throw WriteError("write() failed");
    }
    _buffer.erase(_buffer.begin(), _buffer.begin() + size);
}
