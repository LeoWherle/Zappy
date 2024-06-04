/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Invetory
*/

#include "Inventory.hpp"

Inventory::Inventory(void)
{
    _rocks[Kaillou::FOOD] = 0;
    _rocks[Kaillou::LINEMATE] = 0;
    _rocks[Kaillou::DERAUMERE] = 0;
    _rocks[Kaillou::SIBUR] = 0;
    _rocks[Kaillou::MENDIANE] = 0;
    _rocks[Kaillou::PHIRAS] = 0;
    _rocks[Kaillou::THYSTAME] = 0;
}

void Inventory::setRock(std::map<Kaillou, std::size_t> &rocks)
{
    for (auto &[caillou, num] : rocks) {
        _rocks[caillou] = num;
    }
}

std::size_t Inventory::getNbRock(Kaillou rock)
{
    return _rocks[rock];
}
