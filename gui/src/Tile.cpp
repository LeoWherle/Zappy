/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tile.hpp"

Tile::Tile()
{
}

void Tile::addRock(Kaillou rock)
{
    if (_rocks.find(rock) != _rocks.end()) {
        _rocks[rock]++;
    }
}

void Tile::removeRock(Kaillou rock)
{
    if (_rocks.find(rock) != _rocks.end()) {
        _rocks[rock]--;
    }
}
