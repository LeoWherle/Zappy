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
    }

    void GuiCamera::setUpCam(void)
    {
        _screen = LoadRenderTexture(1920, 1080);
    }

    GuiCamera::~GuiCamera()
    {
        UnloadRenderTexture(_screen);
    }

    void GuiCamera::drawInventory(Pikmin &pikmin)
    {
        DrawRectangle(GetScreenWidth() - 500.0f, 10.0f, 490, GetScreenHeight() - 20, GRAY);
        std::size_t lvl = pikmin.getData().getLevel();
        Inventory inv = pikmin.getData().getInventory();
        std::size_t offset = 1;

        DrawText(("level: " + std::to_string(lvl)).c_str(), GetScreenWidth() - 400.0f, 100 * offset, 12, WHITE);
        offset++;
        for (std::size_t i = 0; i < NBKAILLOU; i++) {
            std::size_t nb = inv.getNbRock(static_cast<Kaillou>(i));
            DrawText(std::to_string(nb).c_str(), GetScreenWidth() - 400.0f, 100 * offset, 12, WHITE);
            offset++;
        }
    }

    void GuiCamera::drawHistory(Pikmin &pikmin)
    {
        return;
    }
}
