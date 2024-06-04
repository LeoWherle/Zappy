/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#pragma once

#include "Material.hpp"
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

enum ModelType {
    DEFAULT, 
    RED_PIKMIN,
    YELLOW_PIKMIN,
    BLUE_PIKMIN,
    LEAF_TOP,
    BUD_TOP,
    FLOWER_TOP
};

enum AnimType {
    WALK,
    INCANTATION,
    IDLE,
    PICK,
    DROP,
    DEATH
};


class GuiModel {
    public:

        GuiModel(std::string modelPath, std::string texturePath, std::string animPath);
        ~GuiModel();

    protected:
    private:
        int _frameCount;
        raylib::Model _model;
        raylib::Texture _texture;
        raylib::Material _material;
        std::vector<raylib::ModelAnimation> _animations;
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
        static const std::map<ModelType, std::vector<AnimType>> animInfo;
        static std::map<ModelType, GuiModel *> models;

        static GuiModel *get(ModelType ressourceName);

        class InvalidModel : public std::exception
        {
            public:
                InvalidModel(std::string name) : _str("invalid model name " + name) {}

                const char* what() const noexcept override { return _str.c_str(); }

            private:
                std::string _str;
        };

};
