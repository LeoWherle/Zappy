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
    _animCount = 0;
    _frameCount = 0;
    _direction = 1;
    _level = 1;
    _position = raylib::Vector3(x, 0, y);
    _motionVector = raylib::Vector3(0, 0, 0);
    _scale = raylib::Vector3(1, 1, 1);
    _colorMod = raylib::Color::White();
}

Pikmin::~Pikmin()
{
    for (auto &anim : _anim) {
        anim.Unload();
    }
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
    if (fileName == "")
        return;
    if (_anim.size() > 0) {
        for (auto &anim : _anim) {
            anim.Unload();
        }
        _animCount = 0;
    }
    _anim = raylib::ModelAnimation::Load(fileName.c_str());
}

bool Pikmin::animationUpdate(void)
{
    if (_model == nullptr || _anim.size() == 0) {
        return false;
    }
    _model->UpdateAnimation(_anim[0], _frameCount);
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

void Pikmin::drawModel(float delta)
{
    _model->Draw(_position, _scale, _colorMod);
}
