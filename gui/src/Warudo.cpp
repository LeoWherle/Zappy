/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Warudo
*/

#include <cstring>
#include "Warudo.hpp"
#include <chrono>

Warudo::Warudo(int timeout, std::string &ip, std::size_t port) : _pikmins(), _map(), _teams(),
    _handler (ActionHandler(_pikmins, _map, _teams, _x, _y)),
    _client (connection::Client(timeout, ip, port))
{
    _run = true;
    InitWindow(1920, 1080, "Zapikmin");
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
            if (std::strncmp(tmp.c_str(), "msz", 3) == 0) {
                _handler(tmp);
                mapReady = true;
            }
            _in.consume(end + 1);
        }
    }
    std::cout << "Map ready" << std::endl;
}

void Warudo::setUp(void)
{
    std::cout << "Initializing the world ..." << std::endl;
    setUpServer();
    setUpMap();
    std::cout << "World initialized" << std::endl;
}

void Warudo::loop()
{
    auto prevTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto curTime = prevTime;

    while (_run && !WindowShouldClose()) {
        //handleCommunication();
        prevTime = curTime;
        curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        _delta = (prevTime - curTime) / 1000;
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
        std::cout << "block" << std::endl;
        while (end != std::string::npos) {
            std::string tmp = inBuff.substr(0, end);
            _handler(tmp);
            inBuff.erase(0, end);
            end = inBuff.find(delimiter);
            consume += end;
        }
        std::cout << "unblock" << std::endl;
        _in.consume(consume);
    }

//    _out.write_to_buffer("mct\n");
    for (auto &player: _pikmins) {
        Pikmin::State status = player.getStatus();
        if (status != Pikmin::State::EGG && status != Pikmin::State::DYING) {
            _out.write_to_buffer("ppo ");
            _out.write_to_buffer(player.getId());
            _out.write_to_buffer("\n");
            _out.write_to_buffer("plv ");
            _out.write_to_buffer(player.getId());
            _out.write_to_buffer("\n");
        }
    }
}

void Warudo::updateGraphic(void)
{
    UpdateCamera(&_cam, CAMERA_FIRST_PERSON);

    BeginDrawing();

    std::size_t index = 0;
    ClearBackground(BLACK);
    for (auto tile : _map) {
        DrawRectangle((index % _x) * 60, (index / _x) * 60, 60, 60, WHITE);
        DrawRectangleLines((index % _x) * 60, (index / _x) * 60, 60, 60, GRAY);  // NOTE: Uses QUADS internally, not lines
        index++;
    }


    BeginMode3D(_cam);

    updateTile();
    updatePikmin();
    updateUI();

    EndMode3D();

    EndDrawing();
}

void Warudo::updatePikmin(void)
{
    for (auto &pikmin : _pikmins) {
        pikmin.animationUpdate();
        pikmin.drawModel(_delta);
    }
}

void Warudo::updateTile(void)
{
    for (auto &tile : _map) {
        //tile update
    }
}

void Warudo::updateUI(void)
{
    // put some blazing bullshit latere
}
