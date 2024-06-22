/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/
#include "ModelBank.hpp"
#include "Functions.hpp"
#include <memory>
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

namespace GUI {
    const std::map<ModelType, ModelBank::ModelInfo> ModelBank::modelInfo = {
        {RED_PIKMIN, {"gui/res/models/RedPikmin.iqm", "gui/res/textures/RedPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {YELLOW_PIKMIN, {"gui/res/models/YellowPikmin.iqm", "gui/res/textures/YellowPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {BLUE_PIKMIN, {"gui/res/models/BluePikmin.iqm", "gui/res/textures/BluePikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {PURPLE_PIKMIN, {"gui/res/models/PurplePikmin.iqm", "gui/res/textures/PurplePikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {WHITE_PIKMIN, {"gui/res/models/WhitePikmin.iqm", "gui/res/textures/WhitePikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {ROCK_PIKMIN, {"gui/res/models/RockPikmin.iqm", "gui/res/textures/RockPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {WING_PIKMIN, {"gui/res/models/WingPikmin.iqm", "gui/res/textures/WingPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {ICE_PIKMIN, {"gui/res/models/IcePikmin.iqm", "gui/res/textures/IcePikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {SPECTRAL_PIKMIN, {"gui/res/models/SpectralPikmin.iqm", "gui/res/textures/SpectralPikmin.png", "gui/res/animations/PikminAnim.iqm"}},
        {FLOWER_TOP, {"gui/res/models/FlowerTop.iqm", "gui/res/textures/FlowerTop.png", "gui/res/animations/PikminAnim.iqm"}},
        {BUD_TOP, {"gui/res/models/BudTop.iqm", "gui/res/textures/BudTop.png", "gui/res/animations/PikminAnim.iqm"}},
        {LEAF_TOP, {"gui/res/models/LeafTop.iqm", "gui/res/textures/LeafTop.png", "gui/res/animations/PikminAnim.iqm"}},
        {FOOD_MOD, {"gui/res/models/Food.glb", "", ""}},
        {LINEMATE_MOD, {"gui/res/models/Linemate.glb", "", ""}},
        {PHIRAS_MOD, {"gui/res/models/Phiras.glb", "", ""}},
        {DERAUMERE_MOD, {"gui/res/models/Deraumere.glb", "", ""}},
        {SIBUR_MOD, {"gui/res/models/Sibur.glb", "", ""}},
        {MENDIANE_MOD, {"gui/res/models/Mendiane.glb", "", ""}},
        {THYSTAME_MOD, {"gui/res/models/Thystame.glb", "", ""}},
        {MAP, {"gui/res/models/Map.glb", "", ""}},
        {WALLS, {"gui/res/models/Walls.glb", "", ""}},
        {RUG, {"gui/res/models/Rug.obj", "gui/res/textures/rug_color.png", ""}}
    };

    std::map<std::string, std::shared_ptr<std::vector<raylib::ModelAnimation>>> ModelBank::loadedAnims;

    std::map<ModelType, std::shared_ptr<GuiModel>> ModelBank::models;

    GuiModel::GuiModel()
    {
        DefaultSetup();
    }

    GuiModel::GuiModel(std::string modelPath, std::string texturePath, std::string animPath, ModelType type)
    {
        _animType = AnimType::NONE;
        if (!raylib::FileExists(modelPath)) {
            DefaultSetup();
            return;
        }
        _type = type;
        _model.Load(modelPath);
        if (raylib::FileExists(texturePath)) {
            _texture.Load(texturePath);
            _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        }
        if (raylib::FileExists(animPath)) {
            if (ModelBank::loadedAnims.find(animPath) == ModelBank::loadedAnims.end())
                ModelBank::loadedAnims[animPath] = std::make_shared<std::vector<raylib::ModelAnimation>>(raylib::ModelAnimation::Load(animPath));
            _animations = ModelBank::loadedAnims[animPath];
        } else
            _animations = nullptr;
        _defaultRotation = -90;
    }

    GuiModel::~GuiModel()
    {
    }

    AnimType GuiModel::GetAnimation()
    {
        return _animType;
    }

    void GuiModel::DefaultSetup()
    {
        _type = DEFAULT;
        raylib::Image image = raylib::Image::Checked(2, 2, 1, 1, raylib::Color::Purple(), raylib::Color::Black());
        _texture.Load(image);
        _model.Load(raylib::Mesh::Cylinder(3, 8, 15));
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
        _animations = nullptr;
        _animType = AnimType::NONE;
    }

    void GuiModel::SetAnimation(AnimType anim)
    {
        _animType = anim;
    }

    void GuiModel::UpdateAnim(int &frameCount)
    {
        if (_animations == nullptr || _animType == AnimType::NONE)
            return;
        _model.UpdateAnimation((*_animations)[_animType], frameCount);
        if (frameCount >= (*_animations)[_animType].frameCount - 2)
            frameCount = 0;
    }

    void GuiModel::Draw(raylib::Vector3 pos, raylib::Vector3 axis, float rotation, float scale, raylib::Color color)
    {
        axis *= rotation;
        axis.x += _defaultRotation;
        axis *= 0.01745329251f;
        _model.transform = MatrixRotateXYZ(axis);
        _model.Draw(pos, scale, color);
    }

    std::shared_ptr<GuiModel> ModelBank::get(ModelType type)
    {
        if (models.find(type) == models.end()) {
            if (modelInfo.find(type) == modelInfo.end()) {
                if (models.find(DEFAULT) == models.end())
                    models[DEFAULT] = std::make_shared<GuiModel>();
                return models[DEFAULT];
            }
            std::string modelPath = modelInfo.at(type).modelPath;
            std::string texturePath = modelInfo.at(type).texturePath;
            std::string animPath = modelInfo.at(type).animPath;
            models[type] = std::make_shared<GuiModel>(modelPath, texturePath, animPath, type);
        }
        return models[type];
    }
}