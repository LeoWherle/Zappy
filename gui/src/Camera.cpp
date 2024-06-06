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
    Camera::Camera() : _direction (raylib::Vector3(0, 1, 0)), _position (raylib::Vector3(0, 0, 0))
    {
        _cam.SetFovy(45.0f);
        _cam.SetProjection(CAMERA_PERSPECTIVE);
        _radius = 0;
        _currAngleX = 45.0f;
        _currAngleY = 0.0f;
        _offsetX = 0;
        _offsetY = 0;
        _minRadius = 2;
    }

    void Camera::setCamPos(void)
    {
        _position = _direction;
        Math::Transformation::rotationX(_currAngleX * M_PI / 180, _position);
        Math::Transformation::rotationY(_currAngleY * M_PI / 180, _position);
        _position = _position * _radius;
        _position.x += _offsetX;
        _position.z += _offsetY;
        _cam.SetPosition(_position);
    }

    void Camera::rotateCamX(int direction)
    {
        float move = ROTATION_SPEED * direction;
        _currAngleX += move;
        if (_currAngleX < _minAngleX) {
            _currAngleX = _minAngleX;
        }
        if (_currAngleX > _maxAngleX) {
            _currAngleX = _maxAngleX;
        }
        setCamPos();
    }

    void Camera::rotateCamY(int direction)
    {
        float move = ROTATION_SPEED * direction;
        _currAngleY += move;
        setCamPos();
    }

    void Camera::changeDistance(int direction)
    {
        float move = ROTATION_SPEED * direction;
        _radius += move / 4;
        if (_radius < _minRadius) {
            _radius = _minRadius;
        }
        setCamPos();
    }

    void Camera::setUpCam(float x, float y)
    {
        /*
            The map center is:
            x / 2
            y / 2
        */
        _offsetX = x / 2.0f;
        _offsetY = y / 2.0f;
        float heightX = (tan(67.5 * M_PI / 180.0f) * (x + 1)) / 2.0f;
        float heightY = (tan(67.5 * M_PI / 180.0f) * (y + 1)) / 2.0f;
        _radius = std::max(heightX, heightY);

        setCamPos();
        _cam.SetTarget(raylib::Vector3(_offsetX, 0.0f, _offsetY));
        _cam.SetUp(raylib::Vector3(0.0f, 1.0f, 0.0f));
    }
}
