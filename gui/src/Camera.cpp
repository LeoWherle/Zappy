/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Camera
*/

#include "Camera.hpp"

namespace GUI {
    Camera::Camera()
    {
        _cam.SetFovy(45.0f);
        _cam.SetProjection(CAMERA_PERSPECTIVE);
    }

    void Camera::setUpCam(float x, float y)
    {
        float heightX = (tan(72.5 * M_PI / 180.0f) * x) / 2.0f;
        float heightY = (tan(72.5 * M_PI / 180.0f) * y) / 2.0f;
        float height = std::max(heightX, heightY);
        raylib:Vector3 camPos = raylib::Vector3(0, height, 0);
        /* rotation X axis, MUST be improved in futur */
        float angle = 45.0f;
    //    float tmpY = camPos.y * cos(angle * M_PI / 180) + camPos.z * -sin(angle * M_PI / 180);
    //    float tmpZ = camPos.y * sin(angle * M_PI / 180) + camPos.z * cos(angle * M_PI / 180);
    //    camPos.y = tmpY;
    //    camPos.z = tmpZ;
        raylib::Matrix rotation = raylib::Matrix::RotateX(angle);
        camPos.x += x / 2.0f;
        camPos.z += y / 2.0f;
        /* rotation X axis, MUST be improved in futur */
        _cam.SetPosition(camPos);
        _cam.SetTarget(raylib::Vector3(x / 2.0f, 0.0f, y / 2.0f));
        _cam.SetUp(raylib::Vector3(0.0f, 1.0f, 0.0f));
    }
}
