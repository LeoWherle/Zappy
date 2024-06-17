/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiCamera
*/

#include "GuiCamera.hpp"
#include "raygui.h"

#include <iostream>
namespace GUI {
    GuiCamera::GuiCamera()
    {
        _sliderVal = 1;
        _prevVal = _sliderVal;
        _pause = false;
        _buttonAction = "Pause";
    }

    void GuiCamera::setUpCam(void)
    {
        _screen = LoadRenderTexture(1920, 1080);
    }

    GuiCamera::~GuiCamera()
    {
        UnloadRenderTexture(_screen);
    }

    void GuiCamera::drawInventory(Pikmin &pikmin)
    {
        DrawRectangle(GetScreenWidth() - 500.0f, 10.0f, 490, GetScreenHeight() - 20, GRAY);
        std::size_t lvl = pikmin.getData().getLevel();
        Inventory inv = pikmin.getData().getInventory();
        std::size_t offset = 1;

        DrawText(("level: " + std::to_string(lvl)).c_str(), GetScreenWidth() - 400.0f, 100 * offset, 12, WHITE);
        offset++;
        for (std::size_t i = 0; i < NBKAILLOU; i++) {
            std::size_t nb = inv.getNbRock(static_cast<Kaillou>(i));
            DrawText(std::to_string(nb).c_str(), GetScreenWidth() - 400.0f, 100 * offset, 12, WHITE);
            offset++;
        }
    }

    void GuiCamera::drawHistory(Pikmin &pikmin)
    {
        return;
    }

    void GuiCamera::handleGui(Buffer::WriteBuffer &out)
    {
        GuiSlider((raylib::Rectangle) {GetScreenWidth() * 75 / 100, 100, 200, 50}, "Tick rate", nullptr, &_sliderVal, 1, 100);
        if (_prevVal != _sliderVal) {
            _prevVal = _sliderVal;
            out.write_to_buffer("sst " + std::to_string(static_cast<int>(_sliderVal)) + "\n");
        }
        if (GuiButton((raylib::Rectangle) {GetScreenWidth() * 25 / 100, 100, 50, 50}, _buttonAction.c_str())) {
            if (_pause) {
                _buttonAction = "Pause";
                _pause = !_pause;
            } else {
                _buttonAction = "Play";
                _pause = !_pause;
            }
            out.write_to_buffer("psd\n");
        }
        if (GuiButton((raylib::Rectangle) {GetScreenWidth() * 50 / 100, 100, 50, 50}, "Next")) {
            _next = true;
            out.write_to_buffer("nxt\n");
        }
    }
}
