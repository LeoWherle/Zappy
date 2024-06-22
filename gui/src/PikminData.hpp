/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin data
*/

#pragma once

#include <string>
#include "Inventory.hpp"

namespace GUI {
    class PikminData
    {
        public:
            PikminData(const std::string &id, std::size_t x, std::size_t y);
            ~PikminData() = default;

            inline void setX(std::size_t val) { _x = val; }
            inline void setY(std::size_t val) { _y = val; }
            inline void setId(std::string &id) { _id = id; }
            inline void setDirection(std::size_t direction) { _direction = direction; }
            inline void setLevel(std::size_t level) { _level = level; }
            inline void setTeam(std::string &team) { _team = team; }
            inline void setInventory(std::map<Kaillou, std::size_t> &inventory) { _inventory.setRock(inventory); }
            inline const std::size_t &getX(void) const { return _x; }
            inline const std::size_t &getY(void) const { return _y; }
            inline const std::string &getId(void) const { return _id; }
            inline const std::size_t &getDirection(void) const { return _direction; }
            inline const std::size_t &getLevel(void) const { return _level; }
            inline const std::string &getTeam(void) const { return _team; }
            inline const Inventory &getInventory(void) const { return _inventory; }

            inline bool operator==(const PikminData &other) { return (_id == other._id); }
            inline bool operator==(const std::string &id) { return (_id == id); }

        private:
            std::size_t _x;
            std::size_t _y;
            std::string _id;
            std::size_t _direction;
            std::size_t _level;
            std::string _team;
            Inventory _inventory;
    };
}