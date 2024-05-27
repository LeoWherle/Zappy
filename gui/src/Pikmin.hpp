/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#pragma once

#include <string>
#include <cstddef>

class Pikmin {
    public:
        Pikmin(std::size_t x, std::size_t y);
        Pikmin(std::string &id, std::size_t x, std::size_t y);
        ~Pikmin() = default;

        inline void setX(std::size_t val) { _x = val; }
        inline void setY(std::size_t val) { _y = val; }
        inline void setId(std::string &id) { _id = id; }

        inline std::size_t getX(void) const { return _x; }
        inline std::size_t getY(void) const { return _y; }

        inline bool operator==(const Pikmin &other) { return (_id == other._id); }
        inline bool operator==(const std::string &id) { return (_id == id); }

    private:
        std::size_t _x;
        std::size_t _y;
        std::string _id;
};
