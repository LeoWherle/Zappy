/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#pragma once

#include <string>
#include <cstddef>
#include <raylib-cpp.hpp>
#include "Kaillou.hpp"

class Pikmin {
    public:
        Pikmin(std::size_t x, std::size_t y);
        Pikmin(std::string &id, std::size_t x, std::size_t y);
        ~Pikmin();

        void pickRock(Kaillou rock);
        void dropRock(Kaillou rock);
        inline void setX(std::size_t val) { _x = val; }
        inline void setY(std::size_t val) { _y = val; }
        inline void setId(std::string &id) { _id = id; }

        inline std::size_t getX(void) const { return _x; }
        inline std::size_t getY(void) const { return _y; }

        inline bool operator==(const Pikmin &other) { return (_id == other._id); }
        inline bool operator==(const std::string &id) { return (_id == id); }

        inline void setModel(Model *model) { _model = model; }
        void setAnimation(std::string fileName);

        void animationUpdate(void);

    private:
        std::size_t _x;
        std::size_t _y;
        std::string _id;
        std::map<Kaillou, std::size_t> _inventory;
        Model *_model;
        ModelAnimation *_anim;
        int _animCount;
        int _frameCount;
};
