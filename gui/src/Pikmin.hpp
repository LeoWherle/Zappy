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
#include <map>
#include "Kaillou.hpp"
#include "PikminData.hpp"
#include "PikminModel.hpp"

namespace GUI {
    class Pikmin {
        public:
            enum Direction {
                NORTH = 1,
                SOUTH = 3,
                EST = 2,
                WEST = 4
            };

            enum State {
                ALIVE,
                EJECT,
                EGG,
                DYING
            };
            Pikmin(const std::string &id, std::size_t x, std::size_t y, std::size_t maxX, std::size_t maxY);
            Pikmin() = delete;
            Pikmin(const Pikmin &) = default;
            ~Pikmin();

            bool draw(float delta);

            bool isOnTile(std::size_t x, std::size_t y);

            void setTeam(std::string &team);

            void updatePosition(std::size_t x, std::size_t y, std::size_t orientation);
            void updateLevel(std::size_t level);
            void updateInventory(std::map<Kaillou, std::size_t> &inventory);
            void eject(void);
            void startIncant(void);
            void stopIncant(bool result);
            void LayingEgg(void);
            void dropRock(Kaillou rock);
            void pickRock(Kaillou rock);
            void die(void);
            void spawnAsEgg(void);
            void spawnAsPikmin(void);

            void move(std::size_t x, std::size_t y);
            void turnLeft(void);
            void turnRight(void);
            void look(void);
            void fork(void);
            void ejecting(void);
            void broadcast(void);

            inline bool operator==(const Pikmin &other) { return (_data == other._data); }
            inline bool operator==(const std::string &id) { return (_data == id); }

            inline State getStatus(void) { return _status; }
            inline void setStatus(State newStatus) { _status = newStatus; }

            inline PikminData &getData(void) { return _data; }
            inline PikminModel &getModel(void) { return _model; }

            bool getColision(raylib::Ray &);
        private:

            PikminData _data;
            PikminModel _model;
            State _status;
            float _newX;
            float _newY;
    };
}
