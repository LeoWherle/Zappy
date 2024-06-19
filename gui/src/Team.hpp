/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#include "ModelBank.hpp"

#pragma once

namespace GUI {
    class Team
    {
    public:
        Team(const std::string &name, const std::shared_ptr<GuiModel> &model, const raylib::Color &color) : _name(name), _model(model), _color(color)
        {}

        std::string &getName(void) { return _name; }
        std::shared_ptr<GuiModel> &getModel(void) { return _model; }
        raylib::Color &getColor(void) { return _color; }
        bool operator==(std::string &name) { return (_name == name); }

    private:
        std::string _name;
        std::shared_ptr<GuiModel> _model;
        raylib::Color _color;
    };
}