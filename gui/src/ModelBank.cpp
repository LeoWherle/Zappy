/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#include "ModelBank.hpp"
#include "raylib.h"

const std::map<ModelType, ModelBank::ModelInfo> ModelBank::modelInfo = {
    {RED_PIKMIN, {"gui/res/models/RedPikmin.iqm", "gui/res/textures/RedPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
    {FLOWER_TOP, {"gui/res/models/FlowerTop.iqm", "gui/res/textures/FlowerTop.png", "gui/res/animations/PikminAnim.iqm"}},
    {BUD_TOP, {"gui/res/models/BudTop.iqm", "gui/res/textures/BudTop.png", "gui/res/animations/PikminAnim.iqm"}},
    {LEAF_TOP, {"gui/res/models/LeafTop.iqm", "gui/res/textures/LeafTop.png", "gui/res/animations/PikminAnim.iqm"}},
};

const std::map<ModelType, std::vector<AnimType>> ModelBank::animInfo = {
    {RED_PIKMIN, {WALK, INCANTATION, IDLE, PICK, DROP, DEATH}},
    {FLOWER_TOP, {WALK, INCANTATION, IDLE, PICK, DROP, DEATH}},
    {BUD_TOP, {WALK, INCANTATION, IDLE, PICK, DROP, DEATH}},
    {LEAF_TOP, {WALK, INCANTATION, IDLE, PICK, DROP, DEATH}},
};

std::map<ModelType, GuiModel *> ModelBank::models;

GuiModel::GuiModel(std::string modelPath, std::string texturePath, std::string animPath)
{
    _model = raylib::Model(modelPath.c_str());
    _texture = raylib::Texture(texturePath.c_str());
    _material = raylib::Material();
    _animations = raylib::ModelAnimation::Load(animPath.c_str());
    _material.SetTexture(MATERIAL_MAP_DIFFUSE, _texture);
    _model.materials[0] = _material;
}

GuiModel *ModelBank::get(ModelType type)
{
    if (models.find(type) == models.end()) {
        if (modelInfo.find(type) == modelInfo.end()) {
            return nullptr;
            //throw ModelBank::InvalidModel(ressourceName);
        }
        std::string modelPath = modelInfo.at(type).modelPath;
        std::string texturePath = modelInfo.at(type).texturePath;
        std::string animPath = modelInfo.at(type).animPath;
        models[type] = new GuiModel(modelPath, texturePath, animPath);
    }
    return models[type];
}

