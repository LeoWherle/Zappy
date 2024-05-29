/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Warudo
*/

#include "Warudo.hpp"

Warudo::Warudo(int timeout, std::string &ip, std::size_t port) : _pikmins(), _map(), _teams(),
    _handler (ActionHandler(_pikmins, _map, _teams)),
    _client (connection::Client(timeout, ip, port))
{
    _client.setUpConnection();
    _run = true;
}

Warudo::~Warudo()
{
}

void Warudo::loop()
{
    while (_run) {
        handleCommunication();
        // some shit
    }
}

void Warudo::handleCommunication(void)
{
    _client.handleSelect(_in, _out, _stdInput, _StdOutput);
    std::string stdinBuff = _stdInput.buffer();
    std::string inBuff = _in.buffer();
    int consumed = 0;
    if (stdinBuff.size() >= 6) {
        if (stdinBuff == "exit\n") {
            _run = false;
        }
        consumed += 6;
    }
    if (inBuff.size() > 0) {
        std::size_t consume = 0;;
        std::string delimiter = "=";
        auto end = inBuff.find(delimiter);
        while (end != std::string::npos) {
            std::string tmp = inBuff.substr(0, end);
            _handler(tmp);
            inBuff.erase(0, end);
            end = inBuff.find(delimiter);
            consume += end;
        }
        _in.consume(consume);
    }

//    _out.write_to_buffer("mct\n");
    for (auto player: _pikmins) {
        _out.write_to_buffer("ppo ");
        _out.write_to_buffer(player.getId());
        _out.write_to_buffer("\n");
        _out.write_to_buffer("plv ");
        _out.write_to_buffer(player.getId());
        _out.write_to_buffer("\n");
    }
}