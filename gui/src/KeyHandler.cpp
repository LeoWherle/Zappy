/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** KeyHandler
*/

#include "KeyHandler.hpp"

namespace GUI {
    KeyHandler::KeyHandler(Camera &cam) : _cam(cam)
    {
        /* raylib handle QWERTY configuration */
        _keyMap = {
            {KEY_W, &KeyHandler::moveCamUp},
            {KEY_S, &KeyHandler::moveCamDown},
            {KEY_A, &KeyHandler::moveCamLeft},
            {KEY_D, &KeyHandler::moveCamRight}
        };
    }

    KeyHandler::~KeyHandler()
    {
    }

    void KeyHandler::update(void)
    {
        for (auto &[val, func] : _keyMap) {
            if (IsKeyDown(val)) {
                (this->*func)();
            }
        }
    }

    void KeyHandler::moveCamUp(void)
    {
        _cam.rotateCamX(-1);
    }

    void KeyHandler::moveCamDown(void)
    {
        _cam.rotateCamX(1);
    }

    void KeyHandler::moveCamRight(void)
    {
        _cam.rotateCamY(1);

    }

    void KeyHandler::moveCamLeft(void)
    {
        _cam.rotateCamY(-1);
    }
}
