/*
** EPITECH PROJECT, 2024
** Map
** File description:
** Model
*/

#include "Map.hpp"
#include "ModelBank.hpp"
#include "Vector3.hpp"
#include <vector>

namespace GUI {

    static const std::vector<raylib::Vector3> mapPositions = {
        raylib::Vector3(-1.1f, -2.37f, 4.75f),
        raylib::Vector3(7.0f, -6.0f, -18.0f),
    };

    Map::Map()
    {
        _furniture = nullptr;
        _walls = nullptr;
        _rug = nullptr;
        _currentPos = 0;
        _scale = 0.05f;
        _rotation = 90;
        _position = mapPositions[0];
        _rotationAxis = raylib::Vector3(1.0f, 0.0f, 0.0f);
        _scaling = 1.0f;
    }

    Map::~Map()
    {
    }

    void Map::setupModels()
    {
        _furniture = ModelBank::get(ModelType::MAP);
        _walls = ModelBank::get(ModelType::WALLS);
        _rug = ModelBank::get(ModelType::RUG);
        _bigSofa = ModelBank::get(ModelType::BIGSOFA);
        _sofa = ModelBank::get(ModelType::SOFA);
    }

    void Map::draw()
    {
        _furniture->Draw(_position * _scaling, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _walls->Draw(_position * _scaling, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _rug->Draw(_position * _scaling, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _bigSofa->Draw(_position * _scaling, _rotationAxis, _rotation, _scale, raylib::Color::White());
        _sofa->Draw(_position * _scaling, _rotationAxis, _rotation, _scale, raylib::Color::White());
    }

    void Map::setScaling(float scale)
    {
        _scale *= scale;
        _scaling = scale;
    }

    void Map::changePosition()
    {
        _currentPos += 1;
        if (_currentPos >= mapPositions.size())
            _currentPos = 0;
        _position = mapPositions[_currentPos];
    }
}
