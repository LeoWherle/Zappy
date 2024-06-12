/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiCamera
*/

#pragma once

#include <raylib-cpp.hpp>
#include "Pikmin.hpp"

namespace GUI {
    class GuiCamera {
        public:
            GuiCamera();
            ~GuiCamera();

            void setUpCam(void);
            inline raylib::RenderTexture &getTexture(void) { return _screen; }
            void drawInventory(Pikmin &pikmin);
            void drawHistory(Pikmin &pikmin);

        private:
            raylib::Camera2D _cam;
            raylib::RenderTexture _screen;
    };
}
