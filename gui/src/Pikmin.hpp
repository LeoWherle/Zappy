/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin
*/

#pragma once

#include <map>
#include <string>
#include <cstddef>
#include "Kaillou.hpp"

class Pikmin {
    enum Direction {
        NORTH = 1,
        SOUTH = 3,
        EST = 2,
        WEST = 4
    };

    public:
        Pikmin(std::size_t x, std::size_t y);
        Pikmin(std::string &id, std::size_t x, std::size_t y);
        Pikmin(std::string &id, std::size_t level, std::size_t x, std::size_t y);
        ~Pikmin() = default;

        void pickRock(Kaillou rock);
        void dropRock(Kaillou rock);
        void eject();
        void startIncantation();
        void failIncantation();
        void levelUp();

        inline void setX(std::size_t val) { _x = val; }
        inline void setY(std::size_t val) { _y = val; }
        inline void setId(std::string &id) { _id = id; }
        inline void setDirection(std::size_t direction) { _direction = direction; }
        inline void setLevel(std::size_t level) { _level = level; }
        inline void setTeam(std::string &team) { _team = team; }
        inline void setInventory(std::map<Kaillou, std::size_t> &inventory) { _inventory = inventory; }

        inline std::size_t getX(void) const { return _x; }
        inline std::size_t getY(void) const { return _y; }
        inline std::string &getId(void) { return _id; }
        inline std::size_t getDirection(void) { return _direction; }
        inline std::size_t getLevel(void) { return _level; }
        inline std::string &getTeam(void) { return _team; }
        inline std::map<Kaillou, std::size_t> &getInventory() { return _inventory; }

        inline bool operator==(const Pikmin &other) { return (_id == other._id); }
        inline bool operator==(const std::string &id) { return (_id == id); }

    private:
        std::size_t _x;
        std::size_t _y;
        std::string _id;
        std::size_t _direction;
        std::size_t _level;
        std::string _team;
        bool _incant;
        std::map<Kaillou, std::size_t> _inventory;
};
