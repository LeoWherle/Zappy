/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiCamera
*/

#pragma once

#include <raylib-cpp.hpp>
#include "Pikmin.hpp"
#include "Communication/WriteBuffer.hpp"

#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

namespace GUI {
    class GuiCamera {
        public:
            GuiCamera();
            ~GuiCamera();

            void setUpCam(void);
            void drawInventory(Pikmin &pikmin);
            void drawHistory(Pikmin &pikmin);
            void handleGui(Buffer::WriteBuffer &out);

        private:
            std::string _buttonAction;
            float _sliderVal;
            float _prevVal;
            bool _pause;
            bool _next;
            raylib::Vector2 _inventoryPosition;
            raylib::Vector2 _inventorySize;
            bool _moving;
            bool _minimized;
    };
}
