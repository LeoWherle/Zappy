/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#pragma once

#include <raylib-cpp.hpp>
#include <optional>
#include "Pikmin.hpp"

namespace GUI {
    class Camera {
        public:
            Camera(std::vector<Pikmin> &);
            ~Camera() = default;
            void rotateCamX(int direction);
            void rotateCamY(int direction);
            void changeDistance(int direction);
            void setUpCam(float x, float y);
            inline raylib::Camera3D &getCam(void) { return _cam; }
            void update();
            void setFocus(Pikmin &focus);
            void unfocus(void);
            void reset();
        private:
            void setCamPos(float x, float y, float z, float radius);

            raylib::Camera3D _cam;
            raylib::Vector3 _position;
            float _radius;
            float _minRadius;
            float _currAngleX;
            float _currAngleY;
            float const _maxAngleX = 80.0f;
            float const _minAngleX = 30.0f;
            float const _rotationSpeed = 2.0f;
            float _offsetX;
            float _offsetY;
            std::vector<Pikmin> &_focus;
            std::string _focusId;
    };
}
