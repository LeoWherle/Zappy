/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** KeyHandler
*/

#pragma once

#include "WorldCamera.hpp"
#include "Pikmin.hpp"

namespace GUI {
    class KeyHandler {
        public:
            KeyHandler(WorldCamera &cam, std::vector<Pikmin> &pikmins);
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
            void changeHitboxDisplay(void);

            std::vector<std::pair<int, void (KeyHandler::*)(void)>> _keyMap;
            WorldCamera &_cam;
            std::vector<Pikmin> &_pikmins;
    };
}