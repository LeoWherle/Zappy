/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include "Pikmin.hpp"
#include "Color.hpp"

Pikmin::Pikmin(std::string id, std::size_t x, std::size_t y)
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
    _frameCount = 0;
    _direction = 1;
    _level = 1;
    _position = raylib::Vector3(x, 1, y);
    _motionVector = raylib::Vector3(0, 0, 0);
    _rotationAxis = raylib::Vector3(1, 0, 0);
    _rotation = -90;
    _scale = raylib::Vector3(0.5, 0.5, 0.5);
    _colorMod = raylib::Color::Brown();
    _cumulatedTime = 0.0f;
    _animationTime = 0.0f;
    _walkTime = 0.0f;
}

Pikmin::~Pikmin()
{
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

}

bool Pikmin::animationUpdate(float delta)
{
    if (_model == nullptr) {
        return true;
    }
    // _cumulatedTime += delta;
    // if (_cumulatedTime >= _animationTime) {
    //     _cumulatedTime = 0.0f;
        _model->animations[0].Update(_model->model, _frameCount);
        _top->animations[0].Update(_top->model, _frameCount);
        _frameCount++;
        if (_frameCount > _model->animations[0].frameCount) {
            _frameCount = 0;
            return true;
        }
    // }
    return false;
}

void Pikmin::levelUp()
{
    _level++;
    if (_level < 4)
        _top = ModelBank::get("LeafTop");
    if (_level >= 4 && _level < 6)
        _top = ModelBank::get("BudTop");
    if (_level >= 6)
        _top = ModelBank::get("FlowerTop");
    if (_level == 1)
        _colorMod = raylib::Color::Brown();
    if (_level == 2)
        _colorMod = raylib::Color::Green();
    if (_level == 4 || _level == 6)
        _colorMod = raylib::Color::White();
    if (_level == 3 || _level == 5 || _level == 7)
        _colorMod = raylib::Color::Yellow();
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
        _model->model.Draw(raylib::Vector3{0, 0, 0}, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _top->model.Draw(raylib::Vector3{0, 0, 0}, _rotationAxis, _rotation, _scale, _colorMod);
    } else {
        DrawCubeV(_position, _scale, _colorMod);
    }
}
