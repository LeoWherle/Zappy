/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Warudo
*/

#include <cstring>
#include "Warudo.hpp"
#include <chrono>

namespace GUI {
    Warudo::Warudo(int timeout, std::string &ip, std::size_t port) :
        _pikmins(), _size(0, 0), _map(), _teams(),
        _mapX(_size.first), _mapY(_size.second), _timeMult(0.0f),
        _handler (ActionHandler(_pikmins, _map, _teams, _size, _timeMult)),
        _key (KeyHandler(_cam, _pikmins)),
        _client (connection::Client(timeout, ip, port)),
        _cam(_pikmins)
    {
        _run = true;
        InitWindow(1920, 1080, "ZapPikmin");
        SetTargetFPS(60);
    }

    Warudo::~Warudo()
    {
    }

    void Warudo::setUpServer(void)
    {
        _client.setUpConnection();
        bool connected = false;
        std::cout << "Connecting to the server..." << std::endl;
        while (!connected) {
            _client.handleSelect(_in, _out, _stdInput, _StdOutput);
            std::string inBuff = _in.buffer();
            if (inBuff.size() > 0) {
                std::string delimiter = "\n";
                auto end = inBuff.find(delimiter);
                std::string tmp = inBuff.substr(0, end);
                if (tmp == "WELCOME") {
                    connected = true;
                    _out.write_to_buffer("GRAPHIC\n");
                }
                _in.consume(end + 1);
            }
        }
        std::cout << "Connected to the server..." << std::endl;
    }

    void Warudo::setUpMap(void)
    {
        std::cout << "Creating the map..." << std::endl;
        _out.write_to_buffer("msz\n");
        bool mapReady = false;
        while (!mapReady) {
            _client.handleSelect(_in, _out, _stdInput, _StdOutput);
            std::string inBuff = _in.buffer();
            if (inBuff.size() > 0) {
                std::string delimiter = "\n";
                auto end = inBuff.find(delimiter);
                std::string tmp = inBuff.substr(0, end);
                if (tmp.substr(0, 3) == "msz") {
                    _handler(tmp);
                    mapReady = true;
                }
                _in.consume(end + 1);
            }
        }
        _cam.setUpCam(_mapX, _mapY);
        std::cout << "Map ready" << std::endl;
    }

    void Warudo::setUp(void)
    {
        std::cout << "Initializing the world ..." << std::endl;
        std::srand(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        setUpServer();
        setUpMap();
        std::cout << "World initialized" << std::endl;
    }

    void Warudo::loop()
    {
        auto prevTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto curTime = prevTime;

        while (_run && !WindowShouldClose()) {
            handleCommunication();
            handleKey();
            _cam.update();
            prevTime = curTime;
            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            _delta = (prevTime - curTime) / 1000 / _timeMult;
            updateGraphic();
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
            std::size_t consume = 0;
            std::string delimiter = "\n";
            auto end = inBuff.find(delimiter);
            while (end != std::string::npos) {
                std::string tmp = inBuff.substr(0, end);
                _handler(tmp);
                inBuff.erase(0, end + 1);
                consume += end + 1;
                end = inBuff.find(delimiter);
            }
            _in.consume(consume + 1);
        }

       _out.write_to_buffer("mct\n");
       for (auto &player: _pikmins) {
           Pikmin::State status = player.getStatus();
           if (status != Pikmin::State::EGG && status != Pikmin::State::DYING) {
               _out.write_to_buffer("ppo ");
               _out.write_to_buffer(player.getData().getId());
               _out.write_to_buffer("\n");
               _out.write_to_buffer("plv ");
               _out.write_to_buffer(player.getData().getId());
               _out.write_to_buffer("\n");
           }
       }
    }

    void Warudo::handleKey(void)
    {
    //    PollInputEvents();
        _key.update();
    }

    void Warudo::updateGraphic(void)
    {
        BeginDrawing();

            ClearWindowState(0);
            ClearBackground(BLACK);
                BeginMode3D(_cam.getCam());

                    std::size_t index = 0;
                    bool line = true;
                    bool white = line;
                    for (auto tile : _map) {
                        if (_mapX == 0 || _mapY == 0)
                            break;
                        raylib::Vector3 pos((index % _mapX), 0, static_cast<int>((index / _mapX)));
                        if (index % _mapX == 0) {
                            line = !line;
                            white = line;
                        }
                        if (white) {
                            DrawCube(pos, 1, 1, 1, WHITE);
                            white = !white;
                        } else {
                            DrawCube(pos, 1, 1, 1, GRAY);
                            white = !white;
                        }
                        index++;
                    }

                    updateTile();
                    updatePikmin();
                    updateUI();

                EndMode3D();

        EndDrawing();
     //   SwapScreenBuffer();
    }

    void Warudo::updatePikmin(void)
    {
        bool animState = false;
        std::vector<std::size_t> toDel;
        for (std::size_t i = 0; i < _pikmins.size(); i++) {
            animState = _pikmins[i].draw(_delta);
            if (_pikmins[i].getStatus() == Pikmin::State::DYING && animState) {
                toDel.push_back(i - toDel.size());
            }
        }
        for (auto del : toDel) {
            _pikmins.erase(_pikmins.begin() + del);
        }
    }

    void Warudo::updateTile(void)
    {
        for (auto &tile : _map) {
            tile.drawTile();
        }
    }

    void Warudo::updateUI(void)
    {
        // put some blazing bullshit latere
    }
};
