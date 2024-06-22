/*
** EPITECH PROJECT, 2024
** Map
** File description:
** Model
*/

#include "Map.hpp"
#include "ModelBank.hpp"

namespace GUI {
    Map::Map()
    {
        _furniture = nullptr;
        _walls = nullptr;
        _rug = nullptr;
        _scale = 0.08;
        _rotation = 90;
        _position = raylib::Vector3(-1.5, -3.3, 8.7);
        _rotationAxis = raylib::Vector3(1, 0, 0);
    }

    Map::~Map()
    {
    }

    void Map::setupModels()
    {
        _furniture = ModelBank::get(ModelType::MAP);
        _walls = ModelBank::get(ModelType::WALLS);
        _rug = ModelBank::get(ModelType::RUG);
    }

    void Map::draw()
    {
        _furniture->Draw(_position, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _walls->Draw(_position, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _rug->Draw(_position, _rotationAxis, _rotation, _scale, raylib::Color::White());
    }
}
