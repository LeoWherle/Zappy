/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Animation bank
*/

#pragma once

#include <map>
#include <string>
#include <raylib-cpp.hpp>

class AnimationBank
{
public:
    AnimationBank() = default;
    ~AnimationBank();

    std::vector<raylib::ModelAnimation> *get(const std::string &ressourceName);
    float getFps(std::string ressourceName);

    class InvalidAnimation : public std::exception
    {
    public:
        InvalidAnimation(const std::string &name) : _str("invalid animation name " + name)
        {}

        const char* what() const noexcept override
        {
            return _str.c_str();
        }

    private:
        std::string _str;
    };
private:
    std::map<std::string, std::vector<raylib::ModelAnimation>> _anims;
};
