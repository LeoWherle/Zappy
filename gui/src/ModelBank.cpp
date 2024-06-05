/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#include "ModelBank.hpp"
#include "Color.hpp"
#include "Image.hpp"
#include "Mesh.hpp"
#include "ModelAnimation.hpp"
#include "raylib.h"
#include <iostream>
#include <memory>
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

const std::map<ModelType, ModelBank::ModelInfo> ModelBank::modelInfo = {
    // {RED_PIKMIN, {"gui/res/models/RedPikmin.iqm", "gui/res/textures/RedPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
    // {FLOWER_TOP, {"gui/res/models/FlowerTop.iqm", "gui/res/textures/FlowerTop.png", "gui/res/animations/PikminAnim.iqm"}},
    // {BUD_TOP, {"gui/res/models/BudTop.iqm", "gui/res/textures/BudTop.png", "gui/res/animations/PikminAnim.iqm"}},
    // {LEAF_TOP, {"gui/res/models/LeafToptest.iqm", "gui/res/textures/LeafTop.png", "gui/res/animations/PikminAnim.iqm"}},
};

std::map<std::string, std::shared_ptr<std::vector<raylib::ModelAnimation>>> ModelBank::loadedAnims;

std::map<ModelType, std::shared_ptr<GuiModel>> ModelBank::models;

GuiModel::GuiModel(std::string modelPath, std::string texturePath, std::string animPath, ModelType type)
{
    if (type == DEFAULT) {
        _type = type;
        _color = raylib::Color::White();
        raylib::Image image = raylib::Image::Checked(2, 2, 1, 1, raylib::Color::Purple(), raylib::Color::Black());
        _texture.Load(image);
        _model.Load(raylib::Mesh::Cylinder(3, 8, 15));
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        _animations = nullptr;
        return;
    }
    _animType = 0;
    _type = type;
    _model.Load(modelPath);
    _texture.Load(texturePath);
    _color = raylib::Color::White();
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    if (ModelBank::loadedAnims.find(animPath) == ModelBank::loadedAnims.end())
        ModelBank::loadedAnims[animPath] = std::make_shared<std::vector<raylib::ModelAnimation>>(raylib::ModelAnimation::Load(animPath));
    _animations = ModelBank::loadedAnims[animPath];
    SetRotation(raylib::Vector3(1, 0, 0), -90);
    SetScale(0.5);
}

GuiModel::~GuiModel()
{
}

int GuiModel::GetAnimation()
{
    return _animType;
}

void GuiModel::SetAnimation(AnimType anim)
{
    _animType = anim;
}

void GuiModel::SetColor(raylib::Color color)
{
    _color = color;
}

void GuiModel::SetScale(float scale)
{
    _scale = scale;
}

void GuiModel::SetPosition(raylib::Vector3 pos)
{
    _position = pos;
}

void GuiModel::SetRotation(raylib::Vector3 axis, float angle)
{
    _model.transform = raylib::Matrix::Rotate(axis, angle);
}

void GuiModel::UpdateAnim(int &frameCount)
{
    if (_animations == nullptr)
        return;
    _model.UpdateAnimation((*_animations)[_animType], frameCount);
    if (frameCount >= (*_animations)[_animType].frameCount)
        frameCount = 0;
}

void GuiModel::Draw()
{
    _model.Draw(_position, _scale, _color);
}

std::shared_ptr<GuiModel> ModelBank::get(ModelType type)
{
    if (models.find(type) == models.end()) {
        if (modelInfo.find(type) == modelInfo.end()) {
            models[DEFAULT] = std::make_shared<GuiModel>("", "", "", DEFAULT);
            return models[DEFAULT];
        }
        std::string modelPath = modelInfo.at(type).modelPath;
        std::string texturePath = modelInfo.at(type).texturePath;
        std::string animPath = modelInfo.at(type).animPath;
        std::cout << "Loading model " << modelPath << std::endl;
        models[type] = std::make_shared<GuiModel>(modelPath, texturePath, animPath, type);
    }
    return models[type];
}

