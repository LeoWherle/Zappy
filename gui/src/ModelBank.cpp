/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/
#include <iostream>
#include "ModelBank.hpp"

// model name | <model file | texture file>
static const std::map<std::string, std::pair<std::string, std::string>> nameFile({
});

ModelBank::ModelBank(void)
{
}

ModelBank::~ModelBank(void)
{
    if (_models.size() > 0) {
        for (auto &[key, value] : _models) {
            value.model.Unload();
            value.texture.Unload();
        }
    }
}

raylib::Model *ModelBank::get(std::string ressourceName)
{
    if (_models.find(ressourceName) == _models.end()) {
        if (nameFile.find(ressourceName) == nameFile.end()) {
            return nullptr;
            //throw ModelBank::InvalidModel(ressourceName);
        }
        _models[ressourceName] = {raylib::Model(nameFile.at(ressourceName).first), raylib::Texture2D(nameFile.at(ressourceName).first)};
        SetMaterialTexture(&_models[ressourceName].model.materials[0], MATERIAL_MAP_DIFFUSE, _models[ressourceName].texture);
    }
    return &_models[ressourceName].model;
}
