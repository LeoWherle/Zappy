/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World
*/

#include <algorithm>
#include <iostream>
#include "World.hpp"

World::World()
{
}

World::~World()
{
}

void World::addPlayer(std::size_t id, std::size_t x, std::size_t y)
{
    for (auto &player : _players) {
        if (player == id) {
            std::cerr << "Why would you add the same player twice, you cheater !!!!" << std::endl;
            return;
        }
    }
    _players.push_back(Pikmin(x, y));
}

void World::removePlayer(std::size_t id)
{
    for (auto &player : _players) {
        if (player == id) {
            _players.erase(std::find(_players.begin(), _players.end(), player));
        }
    }
}
