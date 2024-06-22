/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include <vector>
#include <iostream>
#include "Pikmin.hpp"
#include "Color.hpp"

namespace GUI {
    Pikmin::Pikmin(const std::string &id, std::size_t x, std::size_t y, std::size_t maxX, std::size_t maxY) : _data(id, x, y), _model(x, y, maxX, maxY)
    {
    }

    Pikmin::~Pikmin()
    {
    }

    void Pikmin::updatePosition(std::size_t x, std::size_t y, std::size_t orientation)
    {
        bool isMoving = (x != _data.getX() || y != _data.getY());
        bool isTurning = (orientation != _data.getDirection());
        if (isMoving) {
            if (!_movStack.empty()) {
                _movStack.erase(_movStack.begin());
            }
            _model.setPositionVector(raylib::Vector3(x, 0.5, y));
            if (_movStack.empty()) {
                _model.setMotionVector(raylib::Vector3::Zero());
            } else {
                _model.setMotionVector(_movStack[0]);
            }
            _data.setX(x);
            _data.setY(y);
        }
        if (isTurning) {
            if (!_rotStack.empty()) {
                _rotStack.erase(_rotStack.begin());
            }
            _model.setRotation((630 - (90 * orientation)) % 361);
            if (_rotStack.empty()) {
                _model.setRotationSpeed(0.0f);
            } else {
                _model.setRotationSpeed(_rotStack[0]);
            }
            _data.setDirection(orientation);
        }
        //if ((isMoving || isTurning) && _rotStack.empty() && _movStack.empty()) {
        //    _model.setAnimation(AnimType::IDLE);
        //}
    }

    bool Pikmin::draw(float delta)
    {
        bool result = _model.animationUpdate(delta);
        _model.drawModel(delta);
        return result;
    }


    bool Pikmin::isOnTile(std::size_t x, std::size_t y)
    {
        return (_data.getX() == x && _data.getY() == y);
    }

    void Pikmin::setTeam(Team &team)
    {
        _data.setTeam(team.getName());
        _model.setPikminModel(team.getModel());
        _model.setPikminColor(team.getColor());
    }

    static const std::vector<std::pair<raylib::Color, ModelType>> bulbMap({
        {raylib::Color::Green(), LEAF_TOP},
        {raylib::Color::Yellow(), LEAF_TOP},
        {raylib::Color::Red(), LEAF_TOP},
        {raylib::Color::White(), BUD_TOP},
        {raylib::Color::Yellow(), BUD_TOP},
        {raylib::Color::White(), FLOWER_TOP},
        {raylib::Color::Yellow(), FLOWER_TOP},
        {raylib::Color::Red(), FLOWER_TOP},
    });

    void Pikmin::updateLevel(std::size_t level)
    {
        if (_data.getLevel() != level) {
            _data.setLevel(level);
            if (level != 0) {
                const auto &newModel = bulbMap[level - 1];
                _model.setBulbModel(ModelBank::get(newModel.second));
                _model.setBulbColor(newModel.first);
            }
        }
    }

    void Pikmin::updateInventory(std::map<Kaillou, std::size_t> &inventory)
    {
        _data.setInventory(inventory);
    }

    void Pikmin::eject(void)
    {
        _model.setAnimation(AnimType::FALL);
        _status = Pikmin::State::EJECT;
    }

    void Pikmin::startIncant(void)
    {
        _model.setAnimation(AnimType::INCANTATION);
    }

    void Pikmin::stopIncant(bool result)
    {
        _model.setAnimation(AnimType::IDLE);
        if (result) {
            //_model.setAnimation(_animation.get("level up"));
        } else {
            //_model.setAnimation(_animation.get("failure"));
        }
    }

    void Pikmin::LayingEgg(void)
    {
        //_model.setAnimation(_animation.get("laying egg"));
    }


    void Pikmin::dropRock(void)
    {
        _model.setAnimation(AnimType::DROP);
    }

    void Pikmin::pickRock(void)
    {
        _model.setAnimation(AnimType::PICK);
    }

    void Pikmin::die(void)
    {
        _model.setAnimation(AnimType::DEATH);
        _status = Pikmin::State::DYING;
    }

    void Pikmin::spawnAsEgg(void)
    {
        _status = Pikmin::State::EGG;
        _model.setPikminModel(ModelBank::get(ModelType::RED_PIKMIN));
        _model.setAnimation(AnimType::PLANT);
    }

    void Pikmin::spawnAsPikmin(void)
    {
        _status = Pikmin::State::ALIVE;
        _model.setPikminModel(ModelBank::get(ModelType::RED_PIKMIN));
        _model.setAnimation(AnimType::IDLE);
    }

    bool Pikmin::getColision(raylib::Ray &mousePos)
    {
        return _model.getColision(mousePos);
    }

    void Pikmin::move(std::size_t x, std::size_t y)
    {
        float curX = (float)(_data.getX());
        float curY = (float)(_data.getY());
        float newX = (float)(x);
        float newY = (float)(y);

        if (!_movStack.empty()) {
            curX += _movStack[0].x;
            curY += _movStack[0].z;
        }

        raylib::Vector3 motionVect(newX - curX, 0.0f, newY - curY);
        if (_movStack.empty()) {
            _model.setMotionVector(motionVect);
        }
        _movStack.push_back(motionVect);
        _model.setAnimation(AnimType::WALK);
    }

    void Pikmin::turnLeft(void)
    {
        if (_rotStack.empty()) {
            _model.setRotationSpeed(90.0f);
        }
        _rotStack.push_back(90.0f);
        _model.setAnimation(AnimType::WALK);
    }

    void Pikmin::turnRight(void)
    {
        if (_rotStack.empty()) {
            _model.setRotationSpeed(-90.0f);
        }
        _rotStack.push_back(-90.0f);
        _model.setAnimation(AnimType::WALK);
    }

    void Pikmin::look(void)
    {
        _model.setAnimation(AnimType::LOOK);
    }

    void Pikmin::fork(void)
    {
        //_model.setAnimation(AnimType::FORK);
    }

    void Pikmin::ejecting(void)
    {
        _model.setAnimation(AnimType::PUSH);
    }

    void Pikmin::broadcast(void)
    {
        _model.setAnimation(AnimType::BROADCAST);
    }

}
