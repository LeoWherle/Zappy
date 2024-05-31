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
{
    _rocks[Kaillou::FOOD] = 0;
    _rocks[Kaillou::LINEMATE] = 0;
    _rocks[Kaillou::DERAUMERE] = 0;
    _rocks[Kaillou::SIBUR] = 0;
    _rocks[Kaillou::MENDIANE] = 0;
    _rocks[Kaillou::PHIRAS] = 0;
    _rocks[Kaillou::THYSTAME] = 0;
}

void Tile::setRocks(std::map<Kaillou, std::size_t> &rocks)
{
    for (auto i = rocks.begin(); i != rocks.end(); i++) {
        int delta = rocks[i->first] - _rocks[i->first];
        for (int j = 0; j < delta; j++) {
            addRock(i->first);
        }
    }
    _rocks = rocks;
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
    if (_rocks.find(rock) != _rocks.end()) {
        groundedMaterial newMat;
        newMat.caillou = rock;
        newMat.pos = raylib::Vector3(_x - 0.45f + (float)(std::rand() % 900) / 1000.0f, 0.6, _y - 0.45f + (float)(std::rand() % 900) / 1000.0f);
        _materials.push_back(newMat);
    }
}

void Tile::removeRock(Kaillou rock)
{
    if (_rocks.find(rock) != _rocks.end()) {
        for (auto i = _materials.begin(); i != _materials.end(); i++) {
            if (i->caillou == rock) {
                _materials.erase(i);
                _rocks[rock]--;
                break;
            }
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
    for (auto i = _materials.begin(); i != _materials.end(); i++) {
        if (_models[i->caillou] != nullptr) {
            _models[i->caillou]->Draw(i->pos);
        } else {
            DrawCube(i->pos, 0.1f, 0.1f, 0.1f, colorMap.at(i->caillou));
        }
    }
}
