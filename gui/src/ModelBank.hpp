/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#pragma once

#include <memory>
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

namespace GUI {
    enum ModelType {
        DEFAULT,
        EGG,
        RED_PIKMIN,
        YELLOW_PIKMIN,
        BLUE_PIKMIN,
        LEAF_TOP,
        BUD_TOP,
        FLOWER_TOP,
        FOOD_MOD,
        LINEMATE_MOD,
        DERAUMERE_MOD,
        SIBUR_MOD,
        MENDIANE_MOD,
        PHIRAS_MOD,
        THYSTAME_MOD
    };

    enum AnimType {
        IDLE,
        WALK,
        INCANTATION,
        BROADCAST,
        DEATH,
        PUSH,
        FALL,
        PLANT,
    };

    class GuiModel {
        public:

            GuiModel();
            GuiModel(std::string modelPath, std::string texturePath, std::string animPath, ModelType type);
            ~GuiModel();

            void DefaultSetup();
            void Draw(raylib::Vector3 pos, raylib::Vector3 axis, float rotation, float scale, raylib::Color color);
            void UpdateAnim(int &frameCount);
            AnimType GetAnimation();
            void SetAnimation(AnimType anim);

        protected:
        private:
            float _scale = 1.0f;
            AnimType _animType;
            ModelType _type;
            raylib::Model _model;
            raylib::Texture _texture;
            raylib::Material _material;
            raylib::Color _color;
            float _defaultRotation;
            std::shared_ptr<std::vector<raylib::ModelAnimation>> _animations;
    };

    class ModelBank
    {
        public:

            typedef struct ModelInfo {
                std::string modelPath;
                std::string texturePath;
                std::string animPath;
            } ModelInfo_t;

            static const std::map<ModelType, ModelInfo> modelInfo;
            static std::map<std::string, std::shared_ptr<std::vector<raylib::ModelAnimation>>> loadedAnims;
            static std::map<ModelType, std::shared_ptr<GuiModel>> models;

            static std::shared_ptr<GuiModel> get(ModelType type);
    };
}