/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiCamera
*/

#pragma once

#include "FloatingWindow.hpp"
#include "Pikmin.hpp"
#include "Communication/WriteBuffer.hpp"

namespace GUI {
    class GuiCamera {
        public:
            GuiCamera();
            ~GuiCamera();

            void setUpCam(void);
            void drawInventory(Pikmin &pikmin);
            void handleGui(Buffer::WriteBuffer &out);

            inline FloatingWindow getInventory(void) { return _inventory; };
            inline FloatingWindow getOptions(void) { return _options; };

        private:
            std::string _buttonAction;
            float _sliderVal;
            float _prevVal;
            bool _pause;
            bool _next;
            FloatingWindow _inventory;
            FloatingWindow _options;
    };
}
