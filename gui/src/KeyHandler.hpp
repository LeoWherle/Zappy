/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** KeyHandler
*/

#pragma once

#include "Camera.hpp"
#include "Pikmin.hpp"

namespace GUI {
    class KeyHandler {
        public:
            KeyHandler(Camera &cam, std::vector<Pikmin> &pikmins);
            ~KeyHandler();

            void update(void);
        private:
            void moveCamUp(void);
            void moveCamDown(void);
            void moveCamRight(void);
            void moveCamLeft(void);
            void moveCamForward(void);
            void moveCamBackward(void);
            void setFocus(void);
            void unfocus(void);

            std::vector<std::pair<int, void (KeyHandler::*)(void)>> _keyMap;
            Camera &_cam;
            std::vector<Pikmin> &_pikmins;
    };
}