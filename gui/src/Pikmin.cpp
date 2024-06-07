/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include <vector>
#include "Pikmin.hpp"
#include "Color.hpp"

namespace GUI {
    Pikmin::Pikmin(const std::string &id, std::size_t x, std::size_t y) : _data(id, x, y), _model(x, y)
    {
    }

    Pikmin::~Pikmin()
    {
    }

    void Pikmin::updatePosition(std::size_t x, std::size_t y, int orientation)
    {
        //if ((_data.getX() != x || _data.getY() != y) && _status != Pikmin::State::EJECT) {
        //    _model.setPositionVector(raylib::Vector3(_data.getX(), 1, _data.getY()));
        //    //_model.setAnimation(_animation.get("walk"));
        //    _model.setMotionVector(raylib::Vector3(_data.getX() - x, 0, _data.getY() - y));
        //}
        _model.setPositionVector(raylib::Vector3(x, 0.5, y));
        _data.setX(x);
        _data.setY(y);
        _data.setDirection(orientation);
        _model.setRotation(90 * orientation - 90);
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
        //_model.setAnimation(_animation.get("eject"));
        _status = Pikmin::State::EJECT;
    }

    void Pikmin::startIncant(void)
    {
        //_model.setAnimation(_animation.get("incant"));
    }

    void Pikmin::stopIncant(bool result)
    {
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
        _model.setPikminModel(ModelBank::get(ModelType::RED_PIKMIN));
        //_model.setAnimation(_animation.get("egg"));
    }

    void Pikmin::spawnAsPikmin(void)
    {
        _status = Pikmin::State::ALIVE;
        _model.setPikminModel(ModelBank::get(ModelType::RED_PIKMIN));
        _model.setAnimation(AnimType::WALK);
    }

    bool Pikmin::getColision(raylib::Ray &mousePos)
    {
        return _model.getColision(mousePos);
    }
}
