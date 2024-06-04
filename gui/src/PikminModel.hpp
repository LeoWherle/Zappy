/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#pragma once

#include <raylib-cpp.hpp>

namespace GUI {
    class PikminModel
    {
        public:
            PikminModel(std::size_t x, std::size_t y);
            ~PikminModel() = default;

            inline void setModel(raylib::Model *model) { _model = model; }
            void drawModel(float delta);
            void setAnimation(std::vector<raylib::ModelAnimation> *anim);
            inline void setAnimationFps(float fps) { _animationTime = 1.0F / fps; }

            bool animationUpdate(float delta);

            inline void setMotionVector(raylib::Vector3 newVect) { _motionVector = newVect; }
            inline void setPositionVector(raylib::Vector3 newPos) { _position = newPos; }

            inline void setRotation(float rotation) { _rotation = rotation; }

            inline void setColor(raylib::Color &color) { _colorMod = color; }

        private:
            raylib::Model *_model;
            std::vector<raylib::ModelAnimation> *_anim;
            int _animCount;
            int _frameCount;

            raylib::Vector3 _position;
            raylib::Vector3 _motionVector;
            raylib::Vector3 _rotationAxis;
            float _rotation;
            raylib::Vector3 _scale;
            raylib::Color _colorMod;

            float _cumulatedTime;
            float _animationTime;
            float _walkTime;
    };
}
