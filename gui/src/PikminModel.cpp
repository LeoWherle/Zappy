/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#include "PikminModel.hpp"

namespace GUI {
    PikminModel::PikminModel(std::size_t x, std::size_t y)
    {
        _model = nullptr;
        _bulb = nullptr;
        _animType = AnimType::IDLE;
        _animCount = 0;
        _frameCount = 0;
        _position = raylib::Vector3(x, 0.5f, y);
        _motionVector = raylib::Vector3::Zero();
        _translationVector = raylib::Vector3::Zero();
        _rotationAxis = raylib::Vector3(0.0f, 0.0f, 1.0f);
        _rotation = 0;
        _scale = 0.05;
        _size = (raylib::Vector3(0.8, 1.2, 1) * _scale * 10);
        _boxOffset = raylib::Vector3(-0.5, 0.0f, -0.5) * _scale * 10;
        _entityBox = raylib::BoundingBox(_position + _boxOffset, _position + _size + _boxOffset);
        _pikminColor = raylib::Color::White();
        _bulbColor = raylib::Color::White();
        _cumulatedTime = 0.0f;
        _animationTime = 1.0f;
        _rotationSpeed = 0.0f;
        _curRot = 0.0f;
        _nbFrame = 1;
        _displayHitBox = false;
    }

    void PikminModel::setBulbModel(std::shared_ptr<GuiModel> model)
    {
        _bulb = model;
    }

    void PikminModel::setAnimation(AnimType anim)
    {
        if (anim != _animType) {
            _frameCount = 0;
            _animType = anim;
            _model->SetAnimation(_animType);
            _nbFrame = _model->getNbFrame();
        }
    }

    void PikminModel::setPositionVector(raylib::Vector3 newPos)
    {
        _position = newPos;
        _translationVector = raylib::Vector3::Zero();
        _entityBox.SetMin(_position + _boxOffset);
        _entityBox.SetMax(_position + _size + _boxOffset);
    }

    bool PikminModel::animationUpdate(float delta)
    {
        if (_model == nullptr || _bulb == nullptr) {
            return true;
        }
        _cumulatedTime += delta;
        float goal = _animationTime / _nbFrame;
        while (_cumulatedTime >= goal) {
            _cumulatedTime -= goal;
            _frameCount++;
        }
        if (_frameCount >= _nbFrame) {
            _frameCount = _frameCount % _nbFrame;
            return true;
        }
        return false;
    }

    void PikminModel::drawModel(float delta)
    {
        _curRot += _rotationSpeed * delta;
        if (std::abs(_curRot) > std::abs(_rotationSpeed) * 7.0f)
            _curRot = _rotationSpeed;
        _translationVector += _motionVector * delta;
        if (_translationVector.Length() > _motionVector.Length() * 7.0f)
            _translationVector = _motionVector * 7.0f;
        _entityBox.SetMin(_position + _translationVector + _boxOffset);
        _entityBox.SetMax(_position + _translationVector + _size + _boxOffset);
        if (_displayHitBox)
            _entityBox.Draw();
        if (_model && _bulb) {
            _model->SetAnimation(_animType);
            _bulb->SetAnimation(_animType);
            _model->UpdateAnim(_frameCount);
            _bulb->UpdateAnim(_frameCount);
            _model->Draw(_position + _translationVector, _rotationAxis, _rotation + _curRot, _scale, _pikminColor);
            _bulb->Draw(_position + _translationVector, _rotationAxis, _rotation + _curRot, _scale, _bulbColor);
        } else {
            DrawCubeV(_position + _translationVector, raylib::Vector3(_scale, _scale, _scale), _pikminColor);
        }
    }

    bool PikminModel::getColision(raylib::Ray &mousePos) const
    {
        raylib::RayCollision colision = GetRayCollisionBox(mousePos, _entityBox);
        return colision.hit;
    }

    void PikminModel::setMotionVector(const raylib::Vector3 newVect)
    {
        _motionVector = newVect / 7.0f;
        _translationVector = raylib::Vector3::Zero();
    }

    void PikminModel::setRotationSpeed(const float speed)
    {
        _rotationSpeed = speed / 7.0f;
        _curRot = 0.0f;
    }
}
