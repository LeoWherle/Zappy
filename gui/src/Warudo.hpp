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
#include "WorldCamera.hpp"
#include "GuiCamera.hpp"
#include "ActionHandler.hpp"
#include "KeyHandler.hpp"
#include "Pikmin.hpp"
#include "Tile.hpp"
#include "InputParser.hpp"
#include "Map.hpp"

namespace GUI {
    class Warudo {
        public:
            Warudo(int timeout, InputParser &in);
            ~Warudo();

            void setUp(void);
            void handleCommunication(void);
            void loop(void);
            void updateGraphic(void);

        private:
            void setUpServer(void);
            void handleKey(void);

            void updatePikmin(void);
            void updateTile(void);
            void updateUI(void);
            void endScreenLoop(void);

            std::vector<Pikmin> _pikmins;
            std::pair<std::size_t, std::size_t> _size;
            std::vector<Tile> _map;
            std::vector<Team> _teams;
            std::size_t &_mapX;
            std::size_t &_mapY;
            float _timeMult;
            KeyHandler _key;

            Map _mapModel;

            connection::Client _client;
            Buffer::ReadBuffer _stdInput;
            Buffer::ReadBuffer _in;
            Buffer::WriteBuffer _StdOutput;
            Buffer::WriteBuffer _out;
            bool _run;

            WorldCamera _worldCam;
            GuiCamera _guiCam;

            float _delta;

            bool ref;

            float _frameClock;

            ActionHandler _handler;
    };
}
