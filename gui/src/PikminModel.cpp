/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#include "PikminModel.hpp"
#include <iostream>

namespace GUI {
    PikminModel::PikminModel(std::size_t x, std::size_t y, std::size_t maxX, std::size_t maxY)
    {
        _model = nullptr;
        _bulb = nullptr;
        _animType = AnimType::IDLE;
        _animCount = 0;
        _frameCount = 0;
        _position = raylib::Vector3(x, 0.5f, y);
        _motionVector = raylib::Vector3(0.0f, 0.0f, 0.0f);
        _rotationAxis = raylib::Vector3(0.0f, 0.0f, 1.0f);
        _rotation = 0;
        _scale = 0.05;
        _size = (raylib::Vector3(1, 1, 1) * _scale);
        _boxOffset = raylib::Vector3(-0.5, -0.5, -0.5) * _scale;
        _entityBox = raylib::BoundingBox(_position + _boxOffset, _position + _size + _boxOffset);
        _pikminColor = raylib::Color::White();
        _bulbColor = raylib::Color::White();
        _cumulatedTime = 0.0f;
        _animationTime = 1.0f;
        _rotationSpeed = 0.0f;
        _nbFrame = 1.0f;
        _maxX = maxX;
        _maxY = maxY;
    }

    void PikminModel::setBulbModel(std::shared_ptr<GuiModel> model)
    {
        _bulb = model;
    }

    void PikminModel::setAnimation(AnimType anim)
    {
        _frameCount = 0;
        _animType = anim;
        _nbFrame = _model->getNbFrame();
    }

    float loopVal(float val, float min, float max)
    {
        if (val > max)
            return min;
        if (val < min)
            return max;
        return val;
    }

    void PikminModel::setPositionVector(raylib::Vector3 newPos)
    {
        _position = newPos;
        _position.x = loopVal(_position.x, 0.0f, _maxX);
        _position.y = loopVal(_position.y, 0.0f, _maxY);
        _entityBox.SetMin(_position + _boxOffset);
        _entityBox.SetMax(_position + _size + _boxOffset);
    }

    bool PikminModel::animationUpdate(float delta)
    {
        if (_model == nullptr || _bulb == nullptr) {
            return true;
        }
        _cumulatedTime += delta;
        if (_cumulatedTime >= _animationTime / _nbFrame) {
            _cumulatedTime = 0.0f;
            _frameCount++;
        }
        return (_frameCount == 0);
    }

    void PikminModel::drawModel(float delta)
    {
        _rotation += _rotationSpeed * delta;
        _position += _motionVector * delta;
        _position.x = loopVal(_position.x, 0.0f, _maxX);
        _position.y = loopVal(_position.y, 0.0f, _maxY);
        _entityBox.SetMin(_position + _boxOffset);
        _entityBox.SetMax(_position + _size + _boxOffset);
        _entityBox.Draw();
        if (_model && _bulb) {
            _model->SetAnimation(_animType);
            _bulb->SetAnimation(_animType);
            _model->UpdateAnim(_frameCount);
            _bulb->UpdateAnim(_frameCount);
            _model->Draw(_position, _rotationAxis, _rotation, _scale, _pikminColor);
            _bulb->Draw(_position, _rotationAxis, _rotation, _scale, _bulbColor);
        } else {
            DrawCubeV(_position, raylib::Vector3(_scale, _scale, _scale), _pikminColor);
        }
    }

    bool PikminModel::getColision(raylib::Ray &mousePos) const
    {
        raylib::RayCollision colision = GetRayCollisionBox(mousePos, _entityBox);
        return colision.hit;
    }
}
