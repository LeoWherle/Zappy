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
    enum TextureType {
        DEFAULT_TEX,
        FOOD_TEX,
        LINEMATE_TEX,
        DERAUMERE_TEX,
        SIBUR_TEX,
        MENDIANE_TEX,
        PHIRAS_TEX,
        THYSTAME_TEX
    };

    class GuiTexture {
        public:

            GuiTexture();
            GuiTexture(std::string texturePath, TextureType type);
            ~GuiTexture();

            void DefaultSetup();
            void Draw(raylib::Vector2 pos, raylib::Vector2 axis, float rotation, float scale, raylib::Color color);
        protected:
        private:
           raylib::Texture _texture;
           TextureType _type;
    };

    class TextureBank
    {
        public:

            typedef struct TextureInfo {
                std::string texturePath;
            } TextureInfo_t;

            static const std::map<TextureType, TextureInfo> textureInfo;
            static std::map<TextureType, std::shared_ptr<GuiTexture>> textures;

            static std::shared_ptr<GuiTexture> get(TextureType type);
    };
}