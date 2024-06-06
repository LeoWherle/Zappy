/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Warudo
*/

#pragma once

#include <raylib-cpp.hpp>
#include "Communication/Client.hpp"
#include "Communication/WriteBuffer.hpp"
#include "Communication/ReadBuffer.hpp"
#include "ActionHandler.hpp"
#include "Pikmin.hpp"
#include "Tile.hpp"

class Warudo {
    public:
        Warudo(int timeout, std::string &ip, std::size_t port);
        ~Warudo();

        void setUp(void);
        void handleCommunication(void);
        void loop(void);
        void updateGraphic(void);

    private:
        void setUpServer(void);
        void setUpMap(void);

        void updatePikmin(void);
        void updateTile(void);
        void updateUI(void);

        std::vector<Pikmin> _pikmins;
        std::vector<Tile> _map;
        std::vector<std::string> _teams;
        std::pair<std::size_t, std::size_t> _size;
        std::size_t &_x;
        std::size_t &_y;
        float _timeMult;
        ActionHandler _handler;

        connection::Client _client;
        ReadBuffer _stdInput;
        ReadBuffer _in;
        WriteBuffer _StdOutput;
        WriteBuffer _out;
        bool _run;

        raylib::Camera3D _cam;

        float _delta;
};
