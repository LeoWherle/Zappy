/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#pragma once

#include <raylib-cpp.hpp>

#define ROTATION_SPEED 1

namespace GUI {
    class Camera {
        public:
            Camera();
            ~Camera() = default;
            void rotateCamX(int direction);
            void rotateCamY(int direction);
            void changeDistance(int direction);
            void setUpCam(float x, float y);
            inline raylib::Camera3D &getCam(void) { return _cam; }
        private:
            void setCamPos(void);

            raylib::Camera3D _cam;
            raylib::Vector3 _direction;
            raylib::Vector3 _position;
            float _radius;
            float _currAngleX;
            float _currAngleY;
            float _minRadius;
            float const _maxAngleX = 80;
            float const _minAngleX = 30;
            float _offsetX;
            float _offsetY;
    };
}
