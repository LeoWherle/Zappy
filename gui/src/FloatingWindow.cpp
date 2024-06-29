/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** FloatingWindow
*/

#include "FloatingWindow.hpp"

namespace GUI {
    FloatingWindow::FloatingWindow() :
        _name(""),
        _windowPosition(raylib::Vector2(0, 0)),
        _windowSize(raylib::Vector2(0, 0))
    {
        _moving = false;
        _minimized = false;
    }

    FloatingWindow::FloatingWindow(std::string &name, raylib::Vector2 &pos, raylib::Vector2 &size) :
        _name(name),
        _windowPosition(pos),
        _windowSize(size / 1.5)
    {
        _moving = false;
        _minimized = false;
    }

    void FloatingWindow::floatingWindow(std::function<void()> &func)
    {
        int close_title_size_delta_half =
            (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;

        // window movement input and collision check
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !_moving) {
            Vector2 mouse_position = GetMousePosition();

            Rectangle title_collision_rect = {
                _windowPosition.x, _windowPosition.y,
                _windowSize.x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half),
                RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT
            };

            if (CheckCollisionPointRec(mouse_position, title_collision_rect)) {
                _moving = true;
            }
        }

        // window movement
        if (_moving) {
            Vector2 mouse_delta = GetMouseDelta();
            _windowPosition.x += mouse_delta.x;
            _windowPosition.y += mouse_delta.y;

            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                _moving = false;

                // clamp window position keep it inside the application area
                if (_windowPosition.x < 0)
                    _windowPosition.x = 0;
                else if (_windowPosition.x > GetScreenWidth() - _windowSize.x)
                    _windowPosition.x = GetScreenWidth() - _windowSize.x;
                if (_windowPosition.y < 0)
                    _windowPosition.y = 0;
                else if (_windowPosition.y > GetScreenHeight())
                    _windowPosition.y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
            }
        }

        // window and content drawing
        if (_minimized) {
            GuiStatusBar(
                (Rectangle) {_windowPosition.x, _windowPosition.y, _windowSize.x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, _name.c_str()
            );
            if (GuiButton(
                    (Rectangle
                    ) {_windowPosition.x + _windowSize.x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                       _windowPosition.y + close_title_size_delta_half, RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                       RAYGUI_WINDOW_CLOSEBUTTON_SIZE},
                    "#120#"
                )) {
                _minimized = false;
            }
        } else {
            _minimized = GuiWindowBox((Rectangle) {_windowPosition.x, _windowPosition.y, _windowSize.x, _windowSize.y}, _name.c_str());

            func();

            // draw the resize button/icon
            GuiDrawIcon(71, _windowPosition.x + _windowSize.x - 20, _windowPosition.y + _windowSize.y - 20, 1, WHITE);
        }
    }
}