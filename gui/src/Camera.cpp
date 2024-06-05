/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#include "Camera.hpp"
#include "Transformation.hpp"

#include <iostream>
namespace GUI {
    Camera::Camera() : _direction (raylib::Vector3(0, 0, 0)), _position (raylib::Vector3(0, 0, 0))
    {
        _cam.SetFovy(45.0f);
        _cam.SetProjection(CAMERA_PERSPECTIVE);
        _radius = 0;
    }

    void Camera::setUpCam(float x, float y)
    {
        float heightX = (tan(67.5 * M_PI / 180.0f) * (x + 1)) / 2.0f;
        float heightY = (tan(67.5 * M_PI / 180.0f) * (y + 1)) / 2.0f;
        float radius = std::max(heightX, heightY);

        _direction.y = radius;
        _direction = _direction.Normalize();
        Math::Transformation::rotationX(45.0f * M_PI / 180, _direction);

        _position = _direction * radius;
        _position.x += x / 2.0f;
        _position.z += y / 2.0f;

        _cam.SetPosition(_position);
        _cam.SetTarget(raylib::Vector3(x / 2.0f, 0.0f, y / 2.0f));
        _cam.SetUp(raylib::Vector3(0.0f, 1.0f, 0.0f));
    }
}
