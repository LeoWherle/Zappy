/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include "Pikmin.hpp"

Pikmin::Pikmin(std::size_t x, std::size_t y)
{
    _x = x;
    _y = y;
    _inventory = {
        {FOOD, 0},
        {LINEMATE, 0},
        {DERAUMERE, 0},
        {SIBUR, 0},
        {MENDIANE, 0},
        {PHIRAS, 0},
        {THYSTAME, 0}
    };
    _id = -1;
    _direction = 1;
    _level = 1;
}

Pikmin::Pikmin(std::string &id, std::size_t x, std::size_t y)
{
    _x = x;
    _y = y;
    _inventory = {
        {FOOD, 0},
        {LINEMATE, 0},
        {DERAUMERE, 0},
        {SIBUR, 0},
        {MENDIANE, 0},
        {PHIRAS, 0},
        {THYSTAME, 0}
    };
    _id = id;
    _direction = 1;
    _level = 1;
}

void Pikmin::pickRock(Kaillou rock)
{
    if (_inventory.find(rock) != _inventory.end()) {
        _inventory[rock]++;
    }
}

void Pikmin::dropRock(Kaillou rock)
{
    if (_inventory.find(rock) != _inventory.end()) {
        _inventory[rock]--;
    }
}

void Pikmin::eject()
{
    return;
}

void Pikmin::startIncantation()
{
    _incant = true;
    return;
}

void Pikmin::failIncantation()
{
    _incant = false;
}

void Pikmin::levelUp()
{
    _incant = false;;
    _level++;
}
