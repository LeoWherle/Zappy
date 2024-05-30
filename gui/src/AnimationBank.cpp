/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Animation Bank
*/

#include "AnimationBank.hpp"

//animation name | animation file name
static const std::map<std::string, std::string> nameFile({
    {"egg", {"", ""}}
});

std::string AnimationBank::get(std::string ressourceName)
{
    if (_anims.find(ressourceName) == _anims.end()) {
        if (nameFile.find(ressourceName) == nameFile.end()) {
            return "";
        }
        _anims[ressourceName] = nameFile.at(ressourceName);
    }
    return _anims[ressourceName];
}
