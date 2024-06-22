/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#pragma once

#include <map>
#include <vector>
#include "Kaillou.hpp"
#include "ModelBank.hpp"
#include "Inventory.hpp"

namespace GUI {
    class Tile {
        public:
            Tile(std::size_t x, std::size_t y);
            ~Tile() = default;
            void setRocks(std::map<Kaillou, std::size_t> &rocks);
            void getRockModel(void);
            void addRock(Kaillou rock);
            void removeRock(Kaillou rock);
            void drawTile(void);
        protected:
        private:

            struct groundedMaterial {
                Kaillou caillou = Kaillou::FOOD;
                raylib::Vector3 pos;
                float rotation;
            };

            Inventory _inv;
            std::map<Kaillou, std::shared_ptr<GuiModel>> _models;
            std::vector<groundedMaterial> _materials;
            float _x;
            float _y;
    };
}