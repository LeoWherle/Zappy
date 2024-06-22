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
#include "TextureBank.hpp"

namespace GUI {
    class GuiCamera {
        public:
            GuiCamera();
            ~GuiCamera();

            void setUpCam(void);
            void drawInventory(Pikmin &pikmin);
            void handleGui(Buffer::WriteBuffer &out);
            void displayBroadcast(void);

            inline void setTime(float val) { _sliderVal = val; _prevVal = val; };

            void addMessage(const std::string &message, Pikmin &speaker);

        private:
            std::string _buttonAction;
            float _sliderVal;
            float _prevVal;
            bool _pause;
            bool _next;
            std::vector<std::string> _messages;
            int _maxMsg;
            FloatingWindow _inventory;
            FloatingWindow _options;
            FloatingWindow _broadcast;
    };
}
