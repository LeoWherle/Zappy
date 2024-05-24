/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#pragma once

#include <cstddef>

class Pikmin {
    public:
        Pikmin(std::size_t x, std::size_t y);
        ~Pikmin() = default;
        inline bool operator==(const Pikmin &other) { return (_id == other._id); }
        inline bool operator==(const std::size_t &id) { return (_id == id); }
    protected:
    private:
        std::size_t _x;
        std::size_t _y;
        std::size_t _id;
};
