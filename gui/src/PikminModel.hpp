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
            PikminModel(int x, int y);
            ~PikminModel() = default;

            inline void setPikminModel(std::shared_ptr<GuiModel> model) { _model = model; }
            void setBulbModel(std::shared_ptr<GuiModel> model);
            void drawModel(float delta);
            void setAnimation(AnimType anim);
            inline void setAnimationFps(float fps) { _animationTime = 1.0F / fps; }

            bool animationUpdate(float delta);

            inline void setMotionVector(const raylib::Vector3 newVect) { _motionVector = newVect; }
            void setPositionVector(raylib::Vector3 newPos);

            inline void setRotation(const float rotation) { _rotation = rotation; }

            inline void setPikminColor(const raylib::Color &color) { _pikminColor = color; }
            inline void setBulbColor(const raylib::Color &color) { _bulbColor = color; }

            bool getColision(raylib::Ray &) const;

            inline int getX(void) { return _position.x; }
            inline int getY(void) { return _position.z; }

        private:
            std::shared_ptr<GuiModel> _model;
            std::shared_ptr<GuiModel> _bulb;
            AnimType _animType;
            int _animCount;
            int _frameCount;

            raylib::Vector3 _position;
            raylib::Vector3 _motionVector;
            raylib::Vector3 _rotationAxis;
            float _rotation;
            float _scale;
            raylib::Color _pikminColor;
            raylib::Color _bulbColor;

            float _cumulatedTime;
            float _animationTime;
            float _walkTime;

            raylib::BoundingBox _entityBox;
            raylib::Vector3 _size;
            raylib::Vector3 _boxOffset;
    };
}
