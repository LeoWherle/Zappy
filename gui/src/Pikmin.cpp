/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include "Pikmin.hpp"
#include <iostream>

Pikmin::Pikmin(std::string &id, std::size_t x, std::size_t y) : _data(id, x, y)
{
}

Pikmin::~Pikmin()
{
}

void Pikmin::updatePosition(std::size_t x, std::size_t y, int orientation)
{
    if ((_data.getX() != x || _data.getY() != y) && _status != Pikmin::State::EJECT) {
        _model.setPositionVector(raylib::Vector3(_data.getX(), 1, _data.getY()));
        //_model.setAnimation(_animation.get("walk"));
        _model.setMotionVector(raylib::Vector3(_data.getX() - x, 0, _data.getY() - y));
    }
    _data.setX(x);
    _data.setY(y);
    _data.setDirection(orientation);
    _model.setRotation(90 * orientation);
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

void Pikmin::setTeam(std::string &team)
{
    _data.setTeam(team);
}

void Pikmin::updateLevel(std::size_t level)
{
    if (_data.getLevel() != level) {
        _data.setLevel(level);
        //update model
    }
}

void Pikmin::updateInventory(std::map<Kaillou, std::size_t> &inventory)
{
    _data.setInventory(inventory);
}

void Pikmin::eject(void)
{
    //_model.setAnimation(_animation.get("eject"));
    _status = Pikmin::State::EJECT;
}

void Pikmin::startIncant(void)
{
    //_model.setAnimation(_animation.get("incant"));
}

void Pikmin::stopIncant(bool result)
{
    if (result == true) {
        updateLevel(_data.getLevel() + 1);
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
    //animation where pikmin drop given rock
}

void Pikmin::pickRock(Kaillou rock)
{
    //animation where pikmin pick given rock
}

void Pikmin::die(void)
{
    //_model.setAnimation(_animation.get("death"));
    _status = Pikmin::State::DYING;
}

void Pikmin::spawnAsEgg(void)
{
    _status = Pikmin::State::EGG;
    //_model.setModel(_model.get("egg"));
    //_model.setAnimation(_animation.get("egg"));
}

void Pikmin::spawnAsPikmin(void)
{
    raylib::Color red = raylib::Color::Red();

    _status = Pikmin::State::ALIVE;
    //_model.setModel(_model.get("pikmin"));
    //_model.setAnimation(_animation.get("idle"));
    _model.setColor(red);
}
