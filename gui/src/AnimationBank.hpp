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
    ~AnimationBank() = default;

    std::string get(std::string ressourceName);

    class InvalidAnimation : public std::exception
    {
    public:
        InvalidAnimation(std::string name) : _str("invalid animation name " + name)
        {}

        const char* what() const noexcept override
        {
            return _str.c_str();
        }

    private:
        std::string _str;
    };
private:
    std::map<std::string, std::string> _anims;
};
