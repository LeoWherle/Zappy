/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** World
*/

#pragma once

#include "Tile.hpp"
#include "Pikmin.hpp"

class World {
    public:
        class UnknownPlayer : public std::exception {
            public:
                explicit UnknownPlayer(const std::string &msg): _msg(msg) {}
                explicit UnknownPlayer(const char *msg): _msg(msg) {}
                virtual ~UnknownPlayer() noexcept {};
                const char *what() const noexcept override { return _msg.c_str(); }
            private:
                std::string _msg;
        };

        World();
        ~World();
        Pikmin &getPikmin(std::string &id);
        void addPlayer(std::string &id, std::size_t x, std::size_t y);
        void removePlayer(std::string &id);
    protected:
    private:
        std::vector<Pikmin> _players;
        std::vector<Tile> _map;
};
