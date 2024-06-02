/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#pragma once

#include "ModelAnimation.hpp"
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

typedef struct ModelInfo {
    std::string modelPath;
    std::string texturePath;
} ModelInfo_t;

typedef struct FullModel {
    raylib::Model model;
    raylib::Texture2D texture;
    std::vector<raylib::ModelAnimation> animations;
} FullModel_t;

class ModelBank
{
    public:

        static const std::map<std::string, ModelInfo_t> modelInfo;
        static std::map<std::string, FullModel_t> models;

        static FullModel_t *get(std::string ressourceName);

        class InvalidModel : public std::exception
        {
            public:
                InvalidModel(std::string name) : _str("invalid model name " + name) {}

                const char* what() const noexcept override { return _str.c_str(); }

            private:
                std::string _str;
        };

};
