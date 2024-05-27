/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Action handler
*/

#include "ActionHandler.hpp"

ActionHandler::ActionHandler(std::vector<Pikmin> &pikmins, std::vector<Tile> &map, std::vector<std::string> &teams) :
    _pikmins(pikmins), _map(map), _teams(teams), _x(0), _y(0)
{
    _regexMap = std::vector<std::pair<std::regex, void (ActionHandler::*)(std::smatch &)>>({
        {std::regex("^msz (\\d+) (\\d+)$"), &ActionHandler::setmapSize},
        {std::regex("^bct (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)$"), &ActionHandler::setTileContent},
        {std::regex("^tna ([^\\n]+)$"), &ActionHandler::addTeamName},
        {std::regex("^pnw (\\d+) (\\d+) (\\d+) (1|2|3|4) (\\d+) ([^\\n]+)$"), &ActionHandler::addPlayer},
        {std::regex("^ppo (\\d+) (\\d+) (\\d+) (1|2|3|4)$"), &ActionHandler::setPikminPosition},
        {std::regex("^plv (\\d+) (\\d+)$"), &ActionHandler::setPikminLevel},
        {std::regex("^pin (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) (\\d+)$"), &ActionHandler::setPikminInventory},
        {std::regex("^pex (\\d+)$"), &ActionHandler::setPikminInventory},
        {std::regex("^pbc (\\d+) ([^\\n]+)$"), &ActionHandler::broadcast},
        {std::regex("^pic (\\d+) (\\d+) (\\d+) (\\d+) (\\d+) ...$"), &ActionHandler::startIncantation},
        {std::regex("^pie (\\d+) (\\d+) (\\d+)$"), &ActionHandler::stopIncantation},
        {std::regex("^pfk (\\d+)$"), &ActionHandler::gonnaLayEgg},
        {std::regex("^pdr (\\d+) i$"), &ActionHandler::pikminDropRessource},
        {std::regex("^pgt (\\d+) i$"), &ActionHandler::pikminPickRessource},
        {std::regex("^pdi (\\d+)$"), &ActionHandler::pikminDie},
        {std::regex("^enw (\\d+) (\\d+) (\\d+) (\\d+)$"), &ActionHandler::layedEgg},
        {std::regex("^ebo (\\d+)$"), &ActionHandler::eggHatche},
        {std::regex("^edi (\\d+)$"), &ActionHandler::pikminDie},
    });
}

ActionHandler::~ActionHandler()
{
}

bool ActionHandler::operator()(std::string &action)
{
    for (auto regex : _regexMap) {
        std::smatch match;
        if (std::regex_match(action, match, regex.first)) {
            (this->*regex.second)(match);
            return true;
        }
    }
    return false;
}

void ActionHandler::setmapSize(std::smatch &arg)
{
    _x = std::atoi(arg[1].str().c_str());
    _y = std::atoi(arg[2].str().c_str());
    _map.clear();
    _map = std::vector<Tile>(_x * _y, Tile());
}

void ActionHandler::setTileContent(std::smatch &arg)
{

}

void ActionHandler::addTeamName(std::smatch &arg)
{
    std::string name = arg[1];
}

void ActionHandler::addPlayer(std::smatch &arg)
{

}

void ActionHandler::setPikminPosition(std::smatch &arg)
{

}

void ActionHandler::setPikminLevel(std::smatch &arg)
{

}

void ActionHandler::setPikminInventory(std::smatch &arg)
{

}

void ActionHandler::ejectPikmin(std::smatch &arg)
{

}

void ActionHandler::broadcast(std::smatch &arg)
{

}

void ActionHandler::startIncantation(std::smatch &arg)
{

}

void ActionHandler::stopIncantation(std::smatch &arg)
{

}

void ActionHandler::gonnaLayEgg(std::smatch &arg)
{

}

void ActionHandler::pikminDropRessource(std::smatch &arg)
{

}

void ActionHandler::pikminPickRessource(std::smatch &arg)
{

}

void ActionHandler::pikminDie(std::smatch &arg)
{
    std::string pikminId = arg[1].str();

    for (std::size_t i = 0; i < _pikmins.size(); i++) {
        if (_pikmins[i] == pikminId) {
            _pikmins[i].setAnimation(_animation.get("death"));
        }
    }
}

void ActionHandler::layedEgg(std::smatch &arg)
{
    std::string eggId = arg[1].str();
    std::string pikminId = arg[2].str();
    std::size_t x = std::atoi(arg[3].str().c_str());
    std::size_t y = std::atoi(arg[4].str().c_str());

    _pikmins.push_back(Pikmin(eggId, x, y));
    _pikmins[_pikmins.size() - 1].setModel(_model.get("egg"));
    _pikmins[_pikmins.size() - 1].setAnimation(_animation.get("egg"));
}

void ActionHandler::eggHatche(std::smatch &arg)
{
    std::string eggId = arg[1].str();

    for (std::size_t i = 0; i < _pikmins.size(); i++) {
        if (_pikmins[i] == eggId) {
            _pikmins[i].setModel(_model.get("pikmin"));
            _pikmins[i].setAnimation(_animation.get("birth"));
        }
    }
}
