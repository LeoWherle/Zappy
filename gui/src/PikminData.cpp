/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin data
*/

#include "PikminData.hpp"

namespace GUI {
    PikminData::PikminData(const std::string &id, std::size_t x, std::size_t y)
    {
        _x = x;
        _y = y;
        _id = id;
        _direction = 1;
        _level = 1;
    }
}