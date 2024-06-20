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
        _newX = -1.0f;
        _newY = -1.0f;
    }

    Pikmin::~Pikmin()
    {
    }

    void Pikmin::updatePosition(std::size_t x, std::size_t y, std::size_t orientation)
    {
        if (x == _data.getX() && y == _data.getY() && orientation == _data.getDirection())
            return;
        _model.setPositionVector(raylib::Vector3(x, 0.5, y));
        _model.setMotionVector(raylib::Vector3::Zero());
        _model.setRotationSpeed(0.0f);
        _model.setRotation((630 - (90 * orientation)) % 361);
        _model.setAnimation(AnimType::IDLE);
        _data.setX(x);
        _data.setY(y);
        _data.setDirection(orientation);
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


    void Pikmin::dropRock(Kaillou rock)
    {
        //_model.setAnimation(AnimType::DROP);
    }

    void Pikmin::pickRock(Kaillou rock)
    {
        //_model.setAnimation(AnimType::PICK);
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
        _newX = 0.0f;
        _newY = 0.0f;

        _model.setAnimation(AnimType::WALK);
        _newX = (float)(x);
        _newY = (float)(y);
        _model.setMotionVector(raylib::Vector3(_newX - curX, 0.0f, _newY - curY));
    }

    void Pikmin::turnLeft(void)
    {
        _model.setRotationSpeed(90.0f / 7.0f);
        _model.setAnimation(AnimType::WALK);
    }

    void Pikmin::turnRight(void)
    {
        _model.setRotationSpeed(-90.0f / 7.0f);
        _model.setAnimation(AnimType::WALK);
    }

    void Pikmin::look(void)
    {
        //_model.setAnimation(AnimType::LOOK);
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
