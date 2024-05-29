/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#pragma once

#include <raylib-cpp.hpp>
#include <map>

class ModelBank
{
public:
    ModelBank(void) = default;
    ~ModelBank(void);

    Model *get(std::string ressourceName);

    struct texturedModel {
        Model model;
        Texture2D texture;
    };

    class InvalidModel : public std::exception
    {
    public:
        InvalidModel(std::string name) : _str("invalid model name " + name)
        {}

        const char* what() const noexcept override
        {
            return _str.c_str();
        }

    private:
        std::string _str;
    };

private:
    std::map<std::string, texturedModel> _models;
};
