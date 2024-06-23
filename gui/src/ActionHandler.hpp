/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Action handler
*/

#pragma once

#include <regex>
#include <vector>
#include "Pikmin.hpp"
#include "Tile.hpp"
#include "GuiCamera.hpp"
#include "ModelBank.hpp"
#include "Team.hpp"
#include "WorldCamera.hpp"
#include "Map.hpp"

namespace GUI {

    class ActionHandler
    {
    public:
        ActionHandler(std::vector<Pikmin> &pikmins, std::vector<Tile> &map, std::vector<Team> &teams,
                      std::pair<std::size_t, std::size_t> &size, float &timeMult, GuiCamera &cam,
                      WorldCamera &worldCam, bool &run, Map &mapModel);
        ~ActionHandler();

        bool operator()(std::string &action);

    private:

        void setmapSize(std::smatch &arg);
        void setTileContent(std::smatch &arg);
        void addTeamName(std::smatch &arg);
        void addPlayer(std::smatch &arg);
        void setPikminPosition(std::smatch &arg);
        void setPikminLevel(std::smatch &arg);
        void setPikminInventory(std::smatch &arg);
        void ejectPikmin(std::smatch &arg);
        void broadcast(std::smatch &arg);
        void startIncantation(std::smatch &arg);
        void stopIncantation(std::smatch &arg);
        void gonnaLayEgg(std::smatch &arg);
        void pikminDropRessource(std::smatch &arg);
        void pikminPickRessource(std::smatch &arg);
        void pikminDie(std::smatch &arg);
        void layedEgg(std::smatch &arg);
        void eggHatche(std::smatch &arg);
        void setTimeMult(std::smatch &arg);
        void pikminMoving(std::smatch &arg);
        void pikminTurningRight(std::smatch &arg);
        void pikminTurningLeft(std::smatch &arg);
        void pikminLookingAround(std::smatch &arg);
        void pikminForking(std::smatch &arg);
        void pikminTakeObject(std::smatch &arg);
        void pikminDropObject(std::smatch &arg);
        void pikminEject(std::smatch &arg);
        void endGame(std::smatch &arg);

        std::vector<Pikmin> &_pikmins;
        std::vector<Tile> &_map;
        std::vector<Team> &_teams;
        std::size_t &_x;
        std::size_t &_y;
        GuiCamera &_guiCam;
        std::vector<std::pair<std::regex, void (ActionHandler::*)(std::smatch &)>> _regexMap;
        float &_timeMult;
        WorldCamera &_worldCam;
        bool &_run;
        Map &_mapModel;
        std::size_t _nbTeam;
        std::vector<ModelType> _pikminModels;
    };
}