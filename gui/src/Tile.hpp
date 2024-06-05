/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile
*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include "Kaillou.hpp"
#include "ModelBank.hpp"
#include "Inventory.hpp"

class Tile {
    public:
        Tile(std::size_t x, std::size_t y);
        ~Tile() = default;
        void setRocks(std::map<Kaillou, std::size_t> &rocks);
        void getRockModel(ModelBank &bank);
        void addRock(Kaillou rock);
        void removeRock(Kaillou rock);
        void drawTile(void);
    protected:
    private:

        struct groundedMaterial {
            Kaillou caillou = Kaillou::FOOD;
            raylib::Vector3 pos;
        };

        Inventory _inv;
        std::map<Kaillou, raylib::Model *> _models;
        std::vector<groundedMaterial> _materials;
        float _x;
        float _y;
};
