/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#pragma once

#include <raylib-cpp.hpp>
#include "ModelBank.hpp"

namespace GUI {
    class PikminModel
    {
        public:
            PikminModel(std::size_t x, std::size_t y);
            ~PikminModel() = default;

            inline void setPikminModel(std::shared_ptr<GuiModel> model) { _model = model; }
            void setBulbModel(std::shared_ptr<GuiModel> model);
            void drawModel(float delta);
            void setAnimation(AnimType anim);
            inline void setAnimationLength(float length) { _animationTime = length; }

            bool animationUpdate(float delta);

            void setMotionVector(const raylib::Vector3 newVect);
            void setPositionVector(raylib::Vector3 newPos);

            inline void setRotation(const float rotation) { _rotation = rotation; }

            inline void setPikminColor(const raylib::Color &color) { _pikminColor = color; }
            inline void setBulbColor(const raylib::Color &color) { _bulbColor = color; }

            bool getColision(raylib::Ray &) const;

            inline float getX(void) { return _position.x + _translationVector.x; }
            inline float getY(void) { return _position.z + _translationVector.z; }

            void setRotationSpeed(const float speed);

            void changeHitboxDisplay(void) {_displayHitBox = !_displayHitBox;}

            inline AnimType getAnimation(void) { return _animType; }

        private:
            std::shared_ptr<GuiModel> _model;
            std::shared_ptr<GuiModel> _bulb;
            AnimType _animType;
            int _animCount;
            int _frameCount;

            raylib::Vector3 _position;
            raylib::Vector3 _motionVector;
            raylib::Vector3 _translationVector;
            raylib::Vector3 _rotationAxis;
            float _rotation;
            float _scale;
            raylib::Color _pikminColor;
            raylib::Color _bulbColor;

            float _cumulatedTime;
            float _animationTime;

            raylib::BoundingBox _entityBox;
            raylib::Vector3 _size;
            raylib::Vector3 _boxOffset;

            float _rotationSpeed;
            float _curRot;

            int _nbFrame;

            bool _displayHitBox;
    };
}
