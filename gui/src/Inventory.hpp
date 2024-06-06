/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Invetory
*/

#pragma once

#include <map>
#include "Kaillou.hpp"

class Inventory
{
public:
    Inventory(void);
    ~Inventory(void) = default;

    void setRock(std::map<Kaillou, std::size_t> &rocks);

    std::size_t getNbRock(Kaillou rock);

private:
    std::map<Kaillou, std::size_t> _rocks;
};
