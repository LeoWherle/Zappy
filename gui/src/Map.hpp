/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** Map
*/

#pragma once

#include "ModelBank.hpp"
#include "Vector3.hpp"
#include <memory>

namespace GUI {
    class Map {
        public:
            Map();
            ~Map();

            void draw();
            void setupModels();
            void setScaling(float scale);

        protected:
        private:
            float _scale;
            float _rotation;
            raylib::Vector3 _position;
            raylib::Vector3 _rotationAxis;
            std::shared_ptr<GuiModel> _furniture;
            std::shared_ptr<GuiModel> _walls;
            std::shared_ptr<GuiModel> _rug;
    };
}
