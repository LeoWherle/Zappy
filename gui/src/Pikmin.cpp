/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include "Pikmin.hpp"

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
    _model = nullptr;
    _anim = nullptr;
    _animCount = 0;
    _frameCount = 0;
    _direction = 1;
    _level = 1;
}

Pikmin::~Pikmin()
{
    UnloadModelAnimations(_anim, _animCount);
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

void Pikmin::setAnimation(std::string fileName)
{
    if (_anim) {
        UnloadModelAnimations(_anim, _animCount);
        _animCount = 0;
    }
    _anim = LoadModelAnimations(fileName.c_str(), &_animCount);
}

bool Pikmin::animationUpdate(void)
{
    if (_model == nullptr || _anim == nullptr) {
        return false;
    }
    UpdateModelAnimation(*_model, _anim[0], _frameCount);
    _frameCount++;
    if (_frameCount > _anim[0].frameCount) {
        _frameCount = 0;
        return true;
    }
    return false;
}

void Pikmin::levelUp()
{
    _level++;
}
