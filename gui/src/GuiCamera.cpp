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
        _moving = false;
        _minimized = false;
    }

    void GuiCamera::setUpCam(void)
    {
        _inventorySize = raylib::Vector2(200.0f, 800.0f);
        _inventoryPosition = raylib::Vector2(GetScreenWidth() - _inventorySize.x - 10.0f, 10);
    }

    GuiCamera::~GuiCamera()
    {
    }

    void GuiCamera::drawInventory(Pikmin &pikmin)
    {
        std::string windowName = "Inventory";

        int close_title_size_delta_half =
            (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;

        // window movement input and collision check
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !_moving) {
            Vector2 mouse_position = GetMousePosition();

            Rectangle title_collision_rect = {
                _inventoryPosition.x, _inventoryPosition.y,
                _inventorySize.x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half),
                RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT
            };

            if (CheckCollisionPointRec(mouse_position, title_collision_rect)) {
                _moving = true;
            }
        }

        // window movement
        if (_moving) {
            Vector2 mouse_delta = GetMouseDelta();
            _inventoryPosition.x += mouse_delta.x;
            _inventoryPosition.y += mouse_delta.y;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                _moving = false;

                // clamp window position keep it inside the application area
                if (_inventoryPosition.x < 0)
                    _inventoryPosition.x = 0;
                else if (_inventoryPosition.x > GetScreenWidth() - _inventorySize.x)
                    _inventoryPosition.x = GetScreenWidth() - _inventorySize.x;
                if (_inventoryPosition.y < 0)
                    _inventoryPosition.y = 0;
                else if (_inventoryPosition.y > GetScreenHeight())
                    _inventoryPosition.y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
            }
        }

        // window and content drawing
        if (_minimized) {
            GuiStatusBar(
                (Rectangle) {_inventoryPosition.x, _inventoryPosition.y, _inventorySize.x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, windowName.c_str()
            );
            if (GuiButton(
                    (Rectangle
                    ) {_inventoryPosition.x + _inventorySize.x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                       _inventoryPosition.y + close_title_size_delta_half, RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                       RAYGUI_WINDOW_CLOSEBUTTON_SIZE},
                    "#120#"
                )) {
                _minimized = false;
            }
        } else {
            _minimized = GuiWindowBox((Rectangle) {_inventoryPosition.x, _inventoryPosition.y, _inventorySize.x, _inventorySize.y}, windowName.c_str());
            //Invengtory data
            std::size_t lvl = pikmin.getData().getLevel();
            Inventory inv = pikmin.getData().getInventory();
            std::size_t offset = 1;
            GuiLabel(raylib::Rectangle(_inventoryPosition.x + 20, _inventoryPosition.y + 50 * offset, 100, 50), ("level: " + std::to_string(lvl)).c_str());
            offset++;

            for (std::size_t i = 0; i < NBKAILLOU; i++) {
                std::size_t nb = inv.getNbRock(static_cast<Kaillou>(i));
                GuiLabel(raylib::Rectangle(_inventoryPosition.x + 20, _inventoryPosition.y + 50 * offset, 100, 50), std::to_string(nb).c_str());
                offset++;
            }

            // draw the resize button/icon
            GuiDrawIcon(71, _inventoryPosition.x + _inventorySize.x - 20, _inventoryPosition.y + _inventorySize.y - 20, 1, WHITE);
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
        if (_pause) {
            if (GuiButton((raylib::Rectangle) {GetScreenWidth() * 50 / 100, 100, 50, 50}, "Next")) {
                _next = true;
                out.write_to_buffer("nxt\n");
            }
        }
    }
}
