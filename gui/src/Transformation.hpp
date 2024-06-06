/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Transformation
*/

#pragma once

#include <raylib-cpp.hpp>

namespace Math {
    class Transformation {
        public:
            static raylib::Vector3 &translation(float x, float y, float z, raylib::Vector3 &pos);
            static raylib::Vector3 &rotationX(float angle, raylib::Vector3 &direction);
            static raylib::Vector3 &rotationY(float angle, raylib::Vector3 &direction);
            static raylib::Vector3 &rotationZ(float angle, raylib::Vector3 &direction);
        private:
            static raylib::Vector3 &multiplyVector(raylib::Matrix &mat, raylib::Vector3 &vec);
    };
}
