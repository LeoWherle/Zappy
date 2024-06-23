/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WorldCamera
*/

#include "WorldCamera.hpp"
#include "Transformation.hpp"

#include <iostream>
namespace GUI {
    WorldCamera::WorldCamera(std::vector<Pikmin> &pikmins) :
        _position (raylib::Vector3(0, 0, 0)),
        _focus(pikmins)
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

    WorldCamera::~WorldCamera()
    {
    }

    void WorldCamera::setCamPos(float x, float y, float z, float radius)
    {
        raylib::Vector3 direction(raylib::Vector3(0, 1, 0));

        _position = direction;
        Math::Transformation::rotationX(_currAngleX * M_PI / 180, _position);
        Math::Transformation::rotationY(_currAngleY * M_PI / 180, _position);

        _position = _position * radius;
        _position.x += x;
        _position.y += y;
        _position.z += z;

        _cam.SetPosition(_position);
        _cam.SetTarget(raylib::Vector3(x, y, z));
    }

    void WorldCamera::rotateCamX(int direction)
    {
        float move = _rotationSpeed * direction;
        _currAngleX += move;
        if (_currAngleX < _minAngleX) {
            _currAngleX = _minAngleX;
        }
        if (_currAngleX > _maxAngleX) {
            _currAngleX = _maxAngleX;
        }
    }

    void WorldCamera::rotateCamY(int direction)
    {
        float move = _rotationSpeed * direction;
        _currAngleY += move;
    }

    void WorldCamera::changeDistance(int direction)
    {
        float move = direction * _zoomPower;
        _radius += move / 4;
        if (_radius < _minRadius) {
            _radius = _minRadius;
        }
    }

    void WorldCamera::setUpCam(float x, float y)
    {
        /*
            The map center is (approximated):
            x / 2
            y / 2
        */
        _zoomPower = std::max(x, y) / 10;
        _offsetX = x / 2.0f;
        _offsetY = y / 2.0f;
        float heightX = (tan(67.5 * M_PI / 180.0f) * (x + 1)) / 2.0f;
        float heightY = (tan(67.5 * M_PI / 180.0f) * (y + 1)) / 2.0f;
        _radius = std::max(heightX, heightY);

        _cam.SetUp(raylib::Vector3(0.0f, 1.0f, 0.0f));
    }

    void WorldCamera::setFocus(Pikmin &focus)
    {
        _cam.SetFovy(30.0f);
        std::string newId = focus.getData().getId();
        if (_focusId == newId) {
                //unfocus();
                // key issue
        } else {
            _focusId = newId;
        }
    }

    void WorldCamera::reset()
    {
        _cam.SetFovy(45.0f);
        _currAngleX = 45.0f;
        _currAngleY = 0.0f;
    }

    void WorldCamera::unfocus(void)
    {
        _cam.SetFovy(45.0f);
        _focusId.clear();
        reset();
    }

    void WorldCamera::update()
    {
        if (!_focusId.empty()) {
            for (auto &pikmin : _focus) {
                if (pikmin == _focusId) {
                    _currAngleY += 0.2;
                    setCamPos(pikmin.getModel().getX(), 1, pikmin.getModel().getY(), 5);
                    return;
                }
            }
            unfocus();
        } else {
            setCamPos(_offsetX, 0, _offsetY, _radius);
        }
    }

    std::string WorldCamera::getFocus(void) const
    {
        return (_focusId);
    }
}
