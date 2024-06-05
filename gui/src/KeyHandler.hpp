/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** KeyHandler
*/

#pragma once

#include "Camera.hpp"

namespace GUI {
    class KeyHandler {
        public:
            KeyHandler(Camera &cam);
            ~KeyHandler();

            void update(void);
        private:
            void moveCamUp(void);
            void moveCamDown(void);
            void moveCamRight(void);
            void moveCamLeft(void);

            std::vector<std::pair<int, void (KeyHandler::*)(void)>> _keyMap;
            Camera &_cam;
    };
}