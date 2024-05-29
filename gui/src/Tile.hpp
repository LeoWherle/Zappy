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
#include "Kaillou.hpp"

class Tile {
    public:
        Tile();
        ~Tile() = default;
        inline void setRocks(std::map<Kaillou, std::size_t> &rocks) { _rocks = rocks; }
        void addRock(Kaillou rock);
        void removeRock(Kaillou rock);
    protected:
    private:
        std::map<Kaillou, std::size_t> _rocks;
};
