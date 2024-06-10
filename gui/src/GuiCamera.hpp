/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiCamera
*/

#pragma once

#include <raylib-cpp.hpp>

namespace GUI {
    class GuiCamera {
        public:
            GuiCamera();
            ~GuiCamera();

            inline raylib::RenderTexture &getTexture(void) { return _screen; }

        private:
            raylib::Camera2D _cam;
            raylib::RenderTexture _screen;
    };
}
