/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include "Pikmin.hpp"

class Tile {
    public:
        Tile();
        ~Tile();
        void setRocks(std::map<std::string, std::size_t> &rocks);
        void addPikmin();
        void removePikmin();
    protected:
    private:
        std::size_t _x;
        std::size_t _y;
        std::vector<Pikmin> _pikmins;
        std::map<std::string, std::size_t> _rocks;
};
