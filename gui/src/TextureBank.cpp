/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/
#include "TextureBank.hpp"
#include "Functions.hpp"
#include <memory>
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

namespace GUI {
    const std::map<TextureType, TextureBank::TextureInfo> TextureBank::textureInfo = {
        {FOOD_TEX, {"gui/res/textures/Food.png"}},
        {LINEMATE_TEX, {"gui/res/textures/Linemate.png"}},
        {DERAUMERE_TEX, {"gui/res/textures/Deraumere.png"}},
        {SIBUR_TEX, {"gui/res/textures/Sibur.png"}},
        {MENDIANE_TEX, {"gui/res/textures/Mendiane.png"}},
        {PHIRAS_TEX, {"gui/res/textures/Phiras.png"}},
        {THYSTAME_TEX, {"gui/res/textures/Thystame.png"}}
    };

    std::map<TextureType, std::shared_ptr<GuiTexture>> TextureBank::textures;

    GuiTexture::GuiTexture()
    {
        raylib::Image image = raylib::Image::Checked(2, 2, 1, 1, raylib::Color::Purple(), raylib::Color::Black());
        _texture.Load(image);
        DefaultSetup();
    }

    GuiTexture::GuiTexture(std::string texturePath, TextureType type)
    {
        if (!raylib::FileExists(texturePath)) {
            DefaultSetup();
            return;
        }
        _type = type;
        _texture.Load(texturePath);
    }

    GuiTexture::~GuiTexture()
    {
    }

    void GuiTexture::DefaultSetup()
    {
        raylib::Image image = raylib::Image::Checked(2, 2, 1, 1, raylib::Color::Purple(), raylib::Color::Black());
        _texture.Load(image);
    }

    void GuiTexture::Draw(raylib::Vector2 pos, raylib::Vector2 axis, float rotation, float scale, raylib::Color color)
    {
        _texture.Draw(pos, 0, scale, WHITE);
    }

    std::shared_ptr<GuiTexture> TextureBank::get(TextureType type)
    {
        if (textures.find(type) == textures.end()) {
            if (textureInfo.find(type) == textureInfo.end()) {
                if (textures.find(DEFAULT_TEX) == textures.end())
                    textures[DEFAULT_TEX] = std::make_shared<GuiTexture>();
                return textures[DEFAULT_TEX];
            }
            std::string texturePath = textureInfo.at(type).texturePath;
            textures[type] = std::make_shared<GuiTexture>(texturePath, type);
        }
        return textures[type];
    }
}
