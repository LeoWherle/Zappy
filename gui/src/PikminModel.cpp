/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#include "PikminModel.hpp"

PikminModel::PikminModel(std::size_t x, std::size_t y)
{
    _model = nullptr;
    _animCount = 0;
    _frameCount = 0;
    _position = raylib::Vector3(x, 1, y);
    _motionVector = raylib::Vector3(0, 0, 0);
    _rotationAxis = raylib::Vector3(0, 1, 0);
    _rotation = 0;
    _scale = raylib::Vector3(0.5, 0.5, 0.5);
    _colorMod = raylib::Color::Blue();
    _cumulatedTime = 0.0f;
    _animationTime = 0.0f;
    _walkTime = 0.0f;
}

void PikminModel::setAnimation(std::vector<raylib::ModelAnimation> *anim)
{
    _animCount = 0;
    _anim = anim;
}

bool PikminModel::animationUpdate(float delta)
{
    if (_model == nullptr || _anim == nullptr || _anim->empty()) {
        return true;
    }
    _cumulatedTime += delta;
    if (_cumulatedTime >= _animationTime) {
        _cumulatedTime = 0.0f;
        _model->UpdateAnimation((*_anim)[0], _frameCount);
        _frameCount++;
        if (_frameCount > (*_anim)[0].frameCount) {
            _frameCount = 0;
            return true;
        }
    }
    return false;
}

void PikminModel::drawModel(float delta)
{
    //if (_motionVector != raylib::Vector3::Zero()) {
    //    _walkTime += delta;
    //    _position += _motionVector * (delta / 7);
    //    if (_walkTime > 7.0f) {
    //        _walkTime = 0.0f;
    //        _motionVector = raylib::Vector3::Zero();
    //    }
    //}
    if (_model) {
        _model->Draw(_position, _rotationAxis, _rotation, _scale, _colorMod);
    } else {
        DrawCubeV(_position, _scale, _colorMod);
    }
}
