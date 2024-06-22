/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** FloatingWindow
*/

#pragma once

#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

#include <raylib-cpp.hpp>
#include <functional>
#include "raygui.h"

namespace GUI {
    class FloatingWindow {
        public:
            FloatingWindow();
            FloatingWindow(std::string &name, raylib::Vector2 &pos, raylib::Vector2 &size);
            ~FloatingWindow() = default;

            void floatingWindow(std::function<void()> &func);

            template<typename F, typename... Args>
            static std::function<void()> createDisplay(F &&f, Args &&...args)
            {
                return std::bind(std::forward<F>(f), std::forward<Args>(args)...);
            }

            inline raylib::Vector2 getPosition() { return _windowPosition; };
            inline raylib::Vector2 getSize() { return _windowSize; };

        private:
            bool _moving;
            bool _minimized;
            std::string _name;
            raylib::Vector2 _windowPosition;
            raylib::Vector2 _windowSize;
    };
}
