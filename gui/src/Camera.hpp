/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#pragma once

#include <raylib-cpp.hpp>

namespace GUI {
    class Camera {
        public:
            Camera();
            ~Camera() = default;
            void setUpCam(float x, float y);
            inline raylib::Camera3D &getCam(void) { return _cam; }
        protected:
        private:
            raylib::Camera3D _cam;
    };
}
