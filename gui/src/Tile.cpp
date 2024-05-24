/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tile.hpp"

void Tile::setRocks(std::map<std::string, std::size_t> &rocks)
{
    for (auto &pair : rocks) {
        if (_rocks.find(pair.first) != _rocks.end()) {
            _rocks.at(pair.first) = pair.second;
        }
    }
}
