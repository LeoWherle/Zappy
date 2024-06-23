/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Warudo
*/

#include <cstring>
#include "Warudo.hpp"
#include "KeyHandler.hpp"
#include "raylib.h"
#include <chrono>

namespace GUI {
    Warudo::Warudo(int timeout, InputParser &in) :
        _pikmins(), _size(0, 0), _map(), _teams(),
        _mapX(_size.first), _mapY(_size.second), _timeMult(0.0f),
        _key (KeyHandler(_worldCam, _pikmins)),
        _client (connection::Client(timeout, in.getAdress(), in.getPort())),
        _worldCam (WorldCamera(_pikmins)),
        _guiCam (GuiCamera()),
        _handler (ActionHandler(_pikmins, _map, _teams, _size, _timeMult, _guiCam, _worldCam, _run, _mapModel))
    {
        InitWindow(1920, 1080, "ZapPikmin");
        _guiCam.setUpCam();
        _run = true;
        SetTargetFPS(60);
        ref = in.getRef();
        _frameClock = 0.0f;
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
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
            std::size_t consume = 0;
            std::string delimiter = "\n";
            auto end = inBuff.find(delimiter);
            std::string tmp = inBuff.substr(0, end);
            if (end != std::string::npos) {
                consume = end + 1;
                if (tmp == "WELCOME") {
                    connected = true;
                    _out.write_to_buffer("GRAPHIC\n");
                }
            }
            _in.consume(consume);
        }
        std::cout << "Connected to the server..." << std::endl;
    }

    void Warudo::setUp(void)
    {
        std::cout << "Initializing the world ..." << std::endl;
        std::srand(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        setUpServer();
        _mapModel.setupModels();
        std::cout << "World initialized" << std::endl;
    }

    void Warudo::loop()
    {
        InitAudioDevice();

        raylib::Music music;
        bool isMusic = false;

        if (raylib::FileExists("gui/res/music/mainMusic.mp3")) {
            music = raylib::Music("gui/res/music/mainMusic.mp3");
            music.Play();
            isMusic = true;
        }

        auto prevTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto curTime = prevTime;

        _out.write_to_buffer("msz\n");
        _out.write_to_buffer("sgt\n");
        _out.write_to_buffer("tna\n");
        _out.write_to_buffer("mct\n");
        while (_run && !WindowShouldClose()) {
            if (isMusic) {
                music.Update();
            }
            handleCommunication();
            handleKey();
            _worldCam.update();
            prevTime = curTime;
            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            _delta = (float)(curTime - prevTime) / 1000.0f;
            updateGraphic();
        }
        if (isMusic) {
            music.Stop();
        }
        if (!_run) {
            endScreenLoop();
        }
        CloseAudioDevice();
    }

    void Warudo::endScreenLoop(void)
    {
        raylib::Music music;
        bool isMusic = false;

        if (raylib::FileExists("gui/res/music/endGame.mp3")) {
            music = raylib::Music("gui/res/music/endGame.mp3");
            music.Play();
            isMusic = true;
        }

        auto prevTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        auto curTime = prevTime;
        std::string winMsg = "team " + _pikmins[0].getData().getTeam() + " has won";

        _worldCam.reset();
        while (!WindowShouldClose()) {
            if (isMusic) {
                music.Update();
            }
            handleCommunication();
            _worldCam.update();
            prevTime = curTime;
            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            _delta = (float)(curTime - prevTime) / 1000.0f;
            BeginDrawing();
                ClearWindowState(0);
                ClearBackground(BLACK);
                BeginMode3D(_worldCam.getCam());

                    _mapModel.draw();
                    updatePikmin();

                EndMode3D();
                raylib::DrawText(winMsg, 460, 440, 100, YELLOW);
            EndDrawing();
        }
        if (isMusic) {
            music.Stop();
        }
    }

    void Warudo::handleCommunication(void)
    {
        static bool eofd = false;

        try {
            if (!eofd) {
                _client.handleSelect(_in, _out, _stdInput, _StdOutput);
            }
        } catch (const std::exception &e) {
            eofd = true;
            std::cerr << e.what() << std::endl;
        }

        std::string stdinBuff = _stdInput.buffer();
        std::string inBuff = _in.buffer();
        int consumed = 0;
        if (stdinBuff.size() >= 6) {
            if (stdinBuff == "exit\n") {
                _run = false;
            }
            consumed += 6;
        }

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
        _in.consume(consume);

        if (!ref && !eofd && _timeMult != 0.0f) {
            for (auto &player: _pikmins) {
                Pikmin::State status = player.getStatus();
                if (_run && status != Pikmin::State::EGG && status != Pikmin::State::DYING) {
                    _out.write_to_buffer("ppo ");
                    _out.write_to_buffer(player.getData().getId());
                    _out.write_to_buffer("\n");
                }
            }

            _frameClock += _delta;
            if (_frameClock > (1.0f / _timeMult)) {
                _frameClock = 0.0f;
                _out.write_to_buffer("mct\n");
                for (auto &player: _pikmins) {
                    Pikmin::State status = player.getStatus();
                    if (status != Pikmin::State::EGG && status != Pikmin::State::DYING) {
                        _out.write_to_buffer("plv ");
                        _out.write_to_buffer(player.getData().getId());
                        _out.write_to_buffer("\n");
                        _out.write_to_buffer("pin ");
                        _out.write_to_buffer(player.getData().getId());
                        _out.write_to_buffer("\n");
                    }
                }
            }
        }
    }

    void Warudo::handleKey(void)
    {
        _key.update();
    }

    void Warudo::updateGraphic(void)
    {
        BeginDrawing();
            ClearWindowState(0);
            ClearBackground(BLACK);
            BeginMode3D(_worldCam.getCam());

                if (IsKeyPressed(KEY_SEMICOLON)) {
                    _mapModel.changePosition();
                }
                _mapModel.draw(); // Assuming _modelModel is your model variable

                updateTile();
                updatePikmin();

            EndMode3D();

            updateUI();
        EndDrawing();
    }

    void Warudo::updatePikmin(void)
    {
        bool animState = false;
        std::vector<std::size_t> toDel;
        for (std::size_t i = 0; i < _pikmins.size(); i++) {
            animState = _pikmins[i].draw(_delta * _timeMult);
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
        for (auto pikmin : _pikmins) {
            if (pikmin == _worldCam.getFocus()) {
                _guiCam.drawInventory(pikmin);
            }
        }
        _guiCam.handleGui(_out);
        _guiCam.displayBroadcast();
    }
};
