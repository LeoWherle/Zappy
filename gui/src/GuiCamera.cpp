/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** GuiCamera
*/

#include "GuiCamera.hpp"

namespace GUI {
    GuiCamera::GuiCamera()
    {
        _sliderVal = 1;
        _prevVal = _sliderVal;
        _pause = false;
        _buttonAction = "Pause";
        _maxMsg = 6;
    }

    GuiCamera::~GuiCamera() {}

    void GuiCamera::setUpCam(void)
    {
        raylib::Vector2 size = raylib::Vector2(200.0f, 500.0f);
        raylib::Vector2 position = raylib::Vector2(GetScreenWidth() - size.x - 10.0f, 10.0f);
        std::string name = "Inventory";
        _inventory = FloatingWindow(name, position, size);
        size = raylib::Vector2(400.0f, 224.0f);
        position = raylib::Vector2(10.0f, 10.0f);
        name = "Options";
        _options = FloatingWindow(name, position, size);
        size = raylib::Vector2(400.0f, 625.0f);
        position = raylib::Vector2(10.0f, 240.0f);
        name = "Broadcasts";
        _broadcast = FloatingWindow(name, position, size);
    }

    static const std::map<Kaillou, TextureType> kaillouTex = {
        {FOOD, FOOD_TEX},
        {LINEMATE, LINEMATE_TEX},
        {DERAUMERE, DERAUMERE_TEX},
        {SIBUR, SIBUR_TEX},
        {MENDIANE, MENDIANE_TEX},
        {PHIRAS, PHIRAS_TEX},
        {THYSTAME, THYSTAME_TEX}
    };

    void GuiCamera::drawInventory(Pikmin &pikmin)
    {
        auto func = FloatingWindow::createDisplay([this, &pikmin]() {
            std::size_t lvl = pikmin.getData().getLevel();
            Inventory inv = pikmin.getData().getInventory();
            std::size_t offset = 1;
            GuiLabel(
                raylib::Rectangle(
                    this->_inventory.getPosition().x + 20 / 1.5,
                    this->_inventory.getPosition().y + 50 * offset / 1.5,
                    100 / 1.5, 50 / 1.5
                ),
                ("level: " + std::to_string(lvl)).c_str()
            );
            offset++;

            for (std::size_t i = 0; i < NBKAILLOU; i++) {
                Kaillou val = static_cast<Kaillou>(i);
                std::size_t nb = inv.getNbRock(val);
                if (kaillouTex.find(val) == kaillouTex.end()) {
                    TextureBank::get(DEFAULT_TEX)->Draw(raylib::Vector2(
                        this->_inventory.getPosition().x + 20 / 1.5,
                        this->_inventory.getPosition().y + 50 * offset / 1.5
                    ), 1.0f /  1.5);
                } else {
                    TextureBank::get(kaillouTex.at(val))->Draw(raylib::Vector2(
                        this->_inventory.getPosition().x + 20 / 1.5,
                        this->_inventory.getPosition().y + 50 * offset / 1.5
                    ), 0.08f / 1.5);
                }
                GuiLabel(
                    raylib::Rectangle(
                        this->_inventory.getPosition().x + 80 / 1.5,
                        this->_inventory.getPosition().y + 50 * offset / 1.5, 100 / 1.5, 50 / 1.5
                    ),
                    std::to_string(nb).c_str()
                );
                offset++;
            }
        });

        _inventory.floatingWindow(func);
    }

    void GuiCamera::handleGui(Buffer::WriteBuffer &out)
    {
        auto func = FloatingWindow::createDisplay([this, &out]() {
            GuiSlider(
                (raylib::Rectangle) {(this->_options.getPosition().x + 100) / 1.5, (this->_options.getPosition().y + 150) / 1.5, (270 / 1.5), (50 / 1.5)},
                "Tick rate", nullptr, &_sliderVal, 1, 100
            );
            if (_prevVal != _sliderVal) {
                _prevVal = _sliderVal;
                out.write_to_buffer("sst " + std::to_string(static_cast<int>(_sliderVal)) + "\n");
            }
            if (GuiButton(
                    (raylib::Rectangle) {(this->_options.getPosition().x + 20) / 1.5, (this->_options.getPosition().y + 50) / 1.5, 80 / 1.5, 50 / 1.5}, _buttonAction.c_str()
                )) {
                if (_pause) {
                    _buttonAction = "Pause";
                    _pause = !_pause;
                } else {
                    _buttonAction = "Play";
                    _pause = !_pause;
                }
                out.write_to_buffer("psd\n");
            }
            if (_pause) {
                if (GuiButton((raylib::Rectangle) {(this->_options.getPosition().x + 20) / 1.5, (this->_options.getPosition().y + 100) / 1.5, 80 / 1.5, 50 / 1.5}, "Next")) {
                    _next = true;
                    out.write_to_buffer("nxt\n");
                }
            }
        });

        _options.floatingWindow(func);
    }

    void GuiCamera::displayBroadcast(void)
    {
        auto func = FloatingWindow::createDisplay([this]() {
            int offset = 0;
            for (auto message : this->_messages) {
                if (this->_maxMsg < 1)
                    return;
                GuiLabel(
                    (raylib::Rectangle) {this->_broadcast.getPosition().x + 20 / 1.5,
                    this->_broadcast.getPosition().y + offset * (this->_broadcast.getSize().y / this->_maxMsg ) + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT / 1.5,
                    this->_broadcast.getSize().x - (20 * 2) / 1.5, this->_broadcast.getSize().y / this->_maxMsg / 1.5},
                    message.c_str()
                );
                offset++;
            }
        });

        _broadcast.floatingWindow(func);
    }

    void GuiCamera::addMessage(const std::string &message, Pikmin &speaker)
    {
        std::string newMsg = "Team: " + speaker.getData().getTeam() + " Pikmin: " + speaker.getData().getId() + ": " + message;
        if (_messages.size() >= _maxMsg)
            _messages.erase(_messages.begin());
        _messages.push_back(newMsg);
    }
}
