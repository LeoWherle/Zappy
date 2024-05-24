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

class Tile {
    public:
        Tile() {};
        ~Tile() = default;
        void setRocks(std::map<std::string, std::size_t> &rocks);
    protected:
    private:
        std::map<std::string, std::size_t> _rocks;
};
