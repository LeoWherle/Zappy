/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World
*/

#pragma once

#include "Tile.hpp"
#include "Pikmin.hpp"

class World {
    public:
        World();
        ~World();
        void addPlayer(std::size_t id, std::size_t x, std::size_t y);
        void removePlayer(std::size_t id);
    protected:
    private:
        std::vector<Pikmin> _players;
        std::vector<Tile> _map;
};
