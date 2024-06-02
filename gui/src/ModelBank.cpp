/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#include "ModelBank.hpp"
#include "ModelAnimation.hpp"
#include "raylib.h"
#include <iostream>

// model name | <model file | texture file>
const std::map<std::string, ModelInfo> ModelBank::modelInfo = {
    {"RedPikmin", {"gui/res/models/RedPikmin.iqm", "gui/res/textures/RedPikmin.png"}},
    {"FlowerTop", {"gui/res/models/FlowerTop.iqm", "gui/res/textures/FlowerTop.png"}},
    {"BudTop", {"gui/res/models/BudTop.iqm", "gui/res/textures/BudTop.png"}},
    {"LeafTop", {"gui/res/models/LeafTop.iqm", "gui/res/textures/LeafTop.png"}},
};

std::map<std::string, FullModel_t> ModelBank::models;

FullModel_t *ModelBank::get(std::string ressourceName)
{
    if (models.find(ressourceName) == models.end()) {
        if (modelInfo.find(ressourceName) == modelInfo.end()) {
            return nullptr;
            //throw ModelBank::InvalidModel(ressourceName);
        }
        std::string modelPath = modelInfo.at(ressourceName).modelPath;
        std::string texturePath = modelInfo.at(ressourceName).texturePath;
        models[ressourceName] = FullModel_t{
            raylib::Model(modelPath.c_str()),
            raylib::Texture(texturePath.c_str()),
            raylib::ModelAnimation::Load(modelPath.c_str())
            };
        SetMaterialTexture(&models[ressourceName].model.materials[0], MATERIAL_MAP_DIFFUSE, models[ressourceName].texture);
    }
    return &models[ressourceName];
}

// ModelBank::ModelBank(void)
// {
// }

// ModelBank::~ModelBank(void)
// {
//     for (auto &[key, value] : _models) {
//         UnloadModel(value.model);
//         UnloadTexture(value.texture);
//     }
// }

// raylib::Model *ModelBank::get(std::string ressourceName)
// {
//     if (_models.find(ressourceName) == _models.end()) {
//         if (nameFile.find(ressourceName) == nameFile.end()) {
//             return nullptr;
//             //throw ModelBank::InvalidModel(ressourceName);
//         }
//         _models[ressourceName] = {raylib::Model(nameFile.at(ressourceName).first), raylib::Texture2D(nameFile.at(ressourceName).first)};
//         SetMaterialTexture(&_models[ressourceName].model.materials[0], MATERIAL_MAP_DIFFUSE, _models[ressourceName].texture);
//     }
//     return &_models[ressourceName].model;
// }
