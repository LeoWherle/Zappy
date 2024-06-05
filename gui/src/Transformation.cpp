/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Transformation
*/

#include "Transformation.hpp"

namespace Math {
    raylib::Vector3 &Transformation::translation(float x, float y, float z, raylib::Vector3 &pos)
    {
        pos.x += x;
        pos.y += y;
        pos.z += z;
        return pos;
    }

    raylib::Vector3 &Transformation::multiplyVector(raylib::Matrix &mat, raylib::Vector3 &vec)
    {
        float newX = mat.m0 * vec.x + mat.m4 * vec.y + mat.m8 * vec.z;
        float newY = mat.m1 * vec.x + mat.m5 * vec.y + mat.m9 * vec.z;
        vec.z = mat.m2 * vec.x + mat.m6 * vec.y + mat.m10 * vec.z;
        vec.x = newX;
        vec.y = newY;
        return vec;
    }

    /**
    * @brief rotate a vector on X axis:
    *
    * direction is a normalized vector representing the direction of an object
    */
    raylib::Vector3 &Transformation::rotationX(float angle, raylib::Vector3 &direction)
    {
        raylib::Matrix rotate = raylib::Matrix::RotateX(angle);
        return multiplyVector(rotate, direction);
    }

    /**
    * @brief rotate a vector on Y axis:
    *
    * direction is a normalized vector representing the direction of an object
    */
    raylib::Vector3 &Transformation::rotationY(float angle, raylib::Vector3 &direction)
    {
        raylib::Matrix rotate = raylib::Matrix::RotateY(angle);
        return multiplyVector(rotate, direction);
    }

    /**
    * @brief rotate a vector on Z axis:
    *
    * direction is a normalized vector representing the direction of an object
    */
    raylib::Vector3 &Transformation::rotationZ(float angle, raylib::Vector3 &direction)
    {
        raylib::Matrix rotate = raylib::Matrix::RotateZ(angle);
        return multiplyVector(rotate, direction);
    }
}