/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Animation Bank
*/

#include "AnimationBank.hpp"

//animation name | animation file name
static const std::map<std::string, std::pair<std::string, float>> nameFile({
});
namespace GUI {
    AnimationBank::~AnimationBank(void)
    {
        for (auto &[name, animList] : _anims) {
            for (auto &anim : animList) {
                anim.Unload();
            }
        }
    }

    std::vector<raylib::ModelAnimation> *AnimationBank::get(std::string ressourceName)
    {
        if (_anims.find(ressourceName) == _anims.end()) {
            if (nameFile.find(ressourceName) == nameFile.end()) {
                return nullptr;
            }
            _anims[ressourceName] = raylib::ModelAnimation::Load(ressourceName);
        }
        return &_anims[ressourceName];
    }

    float AnimationBank::getFps(std::string ressourceName)
    {
        if (nameFile.find(ressourceName) == nameFile.end()) {
            return 1.0f;
        }
        return nameFile.at(ressourceName).second;
    }
}
