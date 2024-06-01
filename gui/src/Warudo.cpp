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
    _size(0, 0), _x(_size.first), _y(_size.second), _timeMult(0.0f),
    _handler (ActionHandler(_pikmins, _map, _teams, _size, _timeMult)),
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
    float heightX = (tan(72.5 * M_PI / 180.0f) * _x) / 2.0f;
    float heightY = (tan(72.5 * M_PI / 180.0f) * _y) / 2.0f;
    float height = std::max(heightX, heightY);
    raylib:Vector3 camPos = raylib::Vector3(0, height, 0);
    /* rotation X axis, MUST be improved in futur */
    float angle = 45.0f;
    float tmpY = camPos.y * cos(angle * M_PI / 180) + camPos.z * -sin(angle * M_PI / 180);
    float tmpZ = camPos.y * sin(angle * M_PI / 180) + camPos.z * cos(angle * M_PI / 180);
    camPos.y = tmpY;
    camPos.z = tmpZ;
    camPos.x += _x / 2.0f;
    camPos.z += _y / 2.0f;
    /* rotation X axis, MUST be improved in futur */
    _cam.SetPosition(camPos);                                              // Camera position
    _cam.SetTarget(raylib::Vector3(_x / 2.0f, 0.0f, _y / 2.0f));          // Camera looking at point
    _cam.SetUp(raylib::Vector3(0.0f, 1.0f, 0.0f));                   // Camera up vector (rotation towards target)
    _cam.SetFovy(45.0f);                                       // Camera field-of-view Y
    _cam.SetProjection(CAMERA_PERSPECTIVE);                 // Camera mode type
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
        handleCommunication();
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

//    _out.write_to_buffer("mct\n");
   // for (auto &player: _pikmins) {
   //     Pikmin::State status = player.getStatus();
   //     if (status != Pikmin::State::EGG && status != Pikmin::State::DYING) {
   //         _out.write_to_buffer("ppo ");
   //         _out.write_to_buffer(player.getId());
   //         _out.write_to_buffer("\n");
   //         _out.write_to_buffer("plv ");
   //         _out.write_to_buffer(player.getId());
   //         _out.write_to_buffer("\n");
   //     }
   // }
}

void Warudo::updateGraphic(void)
{
    BeginDrawing();

        ClearWindowState(0);
        ClearBackground(BLACK);
            BeginMode3D(_cam);

                std::size_t index = 0;
                bool line = true;
                bool white = line;
                for (auto tile : _map) {
                    raylib::Vector3 pos((index % _x), 0, static_cast<int>((index / _x)));
                    if (index % _x == 0) {
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
                for (auto &player : _pikmins) {
                    player.drawModel(_delta);
                    if (player.animationUpdate(_delta)) {
                        // dunno
                    } else {
                        // dunno
                    }
                }

                updateTile();
                updatePikmin();
                updateUI();

            EndMode3D();

    EndDrawing();
}

void Warudo::updatePikmin(void)
{
    bool animState = false;
    for (auto &pikmin : _pikmins) {
        animState = pikmin.animationUpdate(_delta);
        pikmin.drawModel(_delta);
        if (pikmin.getStatus() == Pikmin::State::DYING && animState) {
            //erase
        }
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
