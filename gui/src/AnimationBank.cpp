/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Animation Bank
*/

#include "AnimationBank.hpp"

//animation name | animation file name
static const std::map<std::string, std::pair<std::string, float>> nameFile({
    {"egg", {"", 1.0f}}
});

std::string AnimationBank::get(std::string ressourceName)
{
    if (nameFile.find(ressourceName) == nameFile.end()) {
        return "";
    }
    return nameFile.at(ressourceName).first;
}

float AnimationBank::getFps(std::string ressourceName)
{
    if (nameFile.find(ressourceName) == nameFile.end()) {
        return 1.0f;
    }
    return nameFile.at(ressourceName).second;
}
