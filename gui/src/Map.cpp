/*
** EPITECH PROJECT, 2024
** Map
** File description:
** Model
*/

#include "Map.hpp"
#include "ModelBank.hpp"
#include <iostream>

namespace GUI {
    Map::Map()
    {
        _furniture = nullptr;
        _walls = nullptr;
        _rug = nullptr;
        _scale = 0.05f;
        _rotation = 90;
        _position = raylib::Vector3(-1.1f, -2.4f, 4.75f);
        //_position = raylib::Vector3(0.0f, 0.0f, 0.0f);
        _rotationAxis = raylib::Vector3(1.0f, 0.0f, 0.0f);
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

    void Map::setScaling(float scale)
    {
        _scale *= scale;
        _position *= scale;
    }
}
