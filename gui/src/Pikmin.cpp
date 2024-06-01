/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include "Pikmin.hpp"
#include <iostream>

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
    _position = raylib::Vector3(x, 1, y);
    _motionVector = raylib::Vector3(0, 0, 0);
    _rotationAxis = raylib::Vector3(0, 1, 0);
    _rotation = 0;
    _scale = raylib::Vector3(1, 1, 1);
    _colorMod = raylib::Color::Blue();
    _cumulatedTime = 0.0f;
    _animationTime = 0.0f;
    _walkTime = 0.0f;
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

bool Pikmin::animationUpdate(float delta)
{
    if (_model == nullptr || _anim.size() == 0) {
        return true;
    }
    _cumulatedTime += delta;
    if (_cumulatedTime >= _animationTime) {
        _cumulatedTime = 0.0f;
        _model->UpdateAnimation(_anim[0], _frameCount);
        _frameCount++;
        if (_frameCount > _anim[0].frameCount) {
            _frameCount = 0;
            return true;
        }
    }
    return false;
}

void Pikmin::levelUp()
{
    _level++;
}

void Pikmin::drawModel(float delta)
{
    if (_motionVector != raylib::Vector3::Zero()) {
        _walkTime += delta;
        _position += _motionVector * (delta / 7);
        if (_walkTime > 7.0f) {
            _walkTime = 0.0f;
            _motionVector = raylib::Vector3::Zero();
        }
    }
    if (_model) {
        _model->Draw(_position, _rotationAxis, _rotation, _scale, _colorMod);
    } else {
        DrawCubeV(_position, _scale, _colorMod);
    }
}
