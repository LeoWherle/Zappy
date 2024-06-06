/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include "ModelBank.hpp"
#include "raylib.h"

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
    _models[Kaillou::FOOD] = ModelBank::get(ModelType::FOOD_MOD);
    _models[Kaillou::LINEMATE] = ModelBank::get(ModelType::LINEMATE_MOD);
    _models[Kaillou::DERAUMERE] = ModelBank::get(ModelType::DERAUMERE_MOD);
    _models[Kaillou::SIBUR] = ModelBank::get(ModelType::SIBUR_MOD);
    _models[Kaillou::MENDIANE] = ModelBank::get(ModelType::MENDIANE_MOD);
    _models[Kaillou::PHIRAS] = ModelBank::get(ModelType::PHIRAS_MOD);
    _models[Kaillou::THYSTAME] = ModelBank::get(ModelType::THYSTAME_MOD);
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
    {Kaillou::FOOD, raylib::Color::Brown()},
    {Kaillou::LINEMATE, raylib::Color::Yellow()},
    {Kaillou::DERAUMERE, raylib::Color::Orange()},
    {Kaillou::SIBUR, raylib::Color::Blue()},
    {Kaillou::MENDIANE, raylib::Color::Purple()},
    {Kaillou::PHIRAS, raylib::Color::Red()},
    {Kaillou::THYSTAME, raylib::Color::Green()}
};

void Tile::drawTile(void)
{
    for (auto &i : _materials) {
        //if (_models[i.caillou] != nullptr) {
        //    _models[i.caillou]->SetPosition(i.pos);
        //    _models[i.caillou]->Draw();
        //} else {
            DrawCube(i.pos, 0.1f, 0.1f, 0.1f, colorMap.at(i.caillou));
        //}
    }
}
