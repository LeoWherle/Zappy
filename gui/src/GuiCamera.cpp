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
    }

    GuiCamera::~GuiCamera() {}

    void GuiCamera::setUpCam(void)
    {
        raylib::Vector2 size = raylib::Vector2(200.0f, 500.0f);
        raylib::Vector2 position = raylib::Vector2(GetScreenWidth() - size.x - 10.0f, 10.0f);
        std::string name = "Inventory";
        _inventory = FloatingWindow(name, position, size);
        size = raylib::Vector2(300.0f, 224.0f);
        position = raylib::Vector2(10.0f, 10.0f);
        name = "Options";
        _options = FloatingWindow(name, position, size);
    }

    void GuiCamera::drawInventory(Pikmin &pikmin)
    {
        std::string windowName = "Inventory";
        auto func = _inventory.createDisplay([this, &pikmin]() {
            std::size_t lvl = pikmin.getData().getLevel();
            Inventory inv = pikmin.getData().getInventory();
            std::size_t offset = 1;
            GuiLabel(
                raylib::Rectangle(
                    this->getInventory().getPosition().x + 20,
                    this->getInventory().getPosition().y + 50 * offset,
                    100, 50
                ),
                ("level: " + std::to_string(lvl)).c_str()
            );
            offset++;

            for (std::size_t i = 0; i < NBKAILLOU; i++) {
                std::size_t nb = inv.getNbRock(static_cast<Kaillou>(i));
                GuiLabel(
                    raylib::Rectangle(
                        this->getInventory().getPosition().x + 20,
                        this->getInventory().getPosition().y + 50 * offset, 100, 50
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
        std::string windowName = "Options";
        auto func = _options.createDisplay([this, &out]() {
            GuiSlider(
                (raylib::Rectangle) {this->getOptions().getPosition().x + 55, this->getOptions().getPosition().y + 150, 200, 50},
                "Tick rate", nullptr, &_sliderVal, 1, 100
            );
            if (_prevVal != _sliderVal) {
                _prevVal = _sliderVal;
                out.write_to_buffer("sst " + std::to_string(static_cast<int>(_sliderVal)) + "\n");
            }
            if (GuiButton(
                    (raylib::Rectangle) {this->getOptions().getPosition().x + 20, this->getOptions().getPosition().y + 50, 50, 50}, _buttonAction.c_str()
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
                if (GuiButton((raylib::Rectangle) {this->getOptions().getPosition().x + 20, this->getOptions().getPosition().y + 100, 50, 50}, "Next")) {
                    _next = true;
                    out.write_to_buffer("nxt\n");
                }
            }
        });

        _options.floatingWindow(func);
    }
}
