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
            Kaillou caillou;
            raylib::Vector3 pos;
        };

        std::map<Kaillou, std::size_t> _rocks;
        std::map<Kaillou, FullModel_t *> _models;
        std::vector<groundedMaterial> _materials;
        float _x;
        float _y;
};
