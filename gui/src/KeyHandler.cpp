/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** KeyHandler
*/

#include "KeyHandler.hpp"

namespace GUI {
    KeyHandler::KeyHandler(WorldCamera &cam, std::vector<Pikmin> &pikmins) : _cam(cam), _pikmins(pikmins)
    {
        /* raylib handle QWERTY configuration */
        _keyMap = {
            {KEY_W, &KeyHandler::moveCamUp},
            {KEY_S, &KeyHandler::moveCamDown},
            {KEY_A, &KeyHandler::moveCamLeft},
            {KEY_D, &KeyHandler::moveCamRight},
            {KEY_I, &KeyHandler::moveCamForward},
            {KEY_J, &KeyHandler::moveCamBackward},
            {MOUSE_BUTTON_LEFT, &KeyHandler::setFocus},
            {MOUSE_BUTTON_RIGHT, &KeyHandler::unfocus}
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
            if (IsMouseButtonReleased(val)) {
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

    void KeyHandler::moveCamForward(void)
    {
        _cam.changeDistance(-1);
    }

    void KeyHandler::moveCamBackward(void)
    {
        _cam.changeDistance(1);
    }

    void KeyHandler::setFocus(void)
    {
        raylib::Vector2 mousePos = GetMousePosition();
        for (auto &pikmin : _pikmins) {
            raylib::Ray mouseRay(mousePos, _cam.getCam());
            if (pikmin.getColision(mouseRay)) {
                _cam.setFocus(pikmin);
            }
        }
    }

    void KeyHandler::unfocus(void)
    {
        _cam.unfocus();
    }
}
