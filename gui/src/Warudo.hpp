/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Warudo
*/

#pragma once

#include "Client.hpp"
#include "WriteBuffer.hpp"
#include "ReadBuffer.hpp"
#include "ActionHandler.hpp"
#include "Pikmin.hpp"
#include "Tile.hpp"

class Warudo {
    public:
        Warudo(int timeout, std::string &ip, std::size_t port);
        ~Warudo();
        void handleCommunication(void);
        void loop(void);

    private:
        std::vector<Pikmin> _pikmins;
        std::vector<Tile> _map;
        std::vector<std::string> _teams;
        ActionHandler _handler;

        connection::Client _client;
        ReadBuffer _stdInput;
        ReadBuffer _in;
        WriteBuffer _StdOutput;
        WriteBuffer _out;
        bool _run;
};
