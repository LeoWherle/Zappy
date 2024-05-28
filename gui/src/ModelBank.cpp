/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#include "ModelBank.hpp"

static const std::map<std::string, std::pair<std::string, std::string>> nameFile({
    {"egg", {"", ""}}
});

ModelBank::~ModelBank(void)
{
    for (auto &[key, value] : _models) {
        UnloadModel(value.model);
        UnloadTexture(value.texture);
    }
}

Model *ModelBank::get(std::string ressourceName)
{
    if (_models.find(ressourceName) == _models.end()) {
        if (nameFile.find(ressourceName) == nameFile.end()) {
            throw ModelBank::InvalidModel(ressourceName);
        }
        _models[ressourceName] = {Model(), Texture2D()};
        _models[ressourceName].model = LoadModel(nameFile.at(ressourceName).first.c_str());
        _models[ressourceName].texture = LoadTexture(nameFile.at(ressourceName).first.c_str());
        SetMaterialTexture(&_models[ressourceName].model.materials[0], MATERIAL_MAP_DIFFUSE, _models[ressourceName].texture);
    }
    return &_models[ressourceName].model;
}
