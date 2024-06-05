/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include <random>
#include <iostream>

Tile::Tile(std::size_t x, std::size_t y) : _x(x), _y(y)
{}

void Tile::setRocks(std::map<Kaillou, std::size_t> &rocks)
{
    for (auto i = rocks.begin(); i != rocks.end(); i++) {
        std::size_t nbRock = _inv.getNbRock(i->first);
        while (nbRock < rocks[i->first]) {
            addRock(i->first);
            nbRock++;
        }
        while (nbRock > rocks[i->first]) {
            removeRock(i->first);
            nbRock--;
        }
    }
    _inv.setRock(rocks);
}

void Tile::getRockModel(ModelBank &bank)
{
    _models[Kaillou::FOOD] = bank.get("food");
    _models[Kaillou::LINEMATE] = bank.get("linemate");
    _models[Kaillou::DERAUMERE] = bank.get("deraumere");
    _models[Kaillou::SIBUR] = bank.get("sibur");
    _models[Kaillou::MENDIANE] = bank.get("mendiane");
    _models[Kaillou::PHIRAS] = bank.get("phiras");
    _models[Kaillou::THYSTAME] = bank.get("thystame");
}

void Tile::addRock(Kaillou rock)
{
    groundedMaterial newMat;
    newMat.caillou = rock;
    newMat.pos = raylib::Vector3(_x - 0.45f + (float)(std::rand() % 900) / 1000.0f, 0.6, _y - 0.45f + (float)(std::rand() % 900) / 1000.0f);
    _materials.push_back(newMat);
}

void Tile::removeRock(Kaillou rock)
{
    for (auto i = _materials.begin(); i != _materials.end(); i++) {
        if (i->caillou == rock) {
            _materials.erase(i);
            break;
        }
    }
}

static const std::map<Kaillou, raylib::Color> colorMap = {
    {FOOD, raylib::Color::Brown()},
    {LINEMATE, raylib::Color::Yellow()},
    {DERAUMERE, raylib::Color::Orange()},
    {SIBUR, raylib::Color::Blue()},
    {MENDIANE, raylib::Color::Purple()},
    {PHIRAS, raylib::Color::Red()},
    {THYSTAME, raylib::Color::Green()}
};

void Tile::drawTile(void)
{
    for (auto &i : _materials) {
        if (_models[i.caillou] != nullptr) {
            _models[i.caillou]->Draw(i.pos);
        } else {
            DrawCube(i.pos, 0.1f, 0.1f, 0.1f, colorMap.at(i.caillou));
        }
    }
}
