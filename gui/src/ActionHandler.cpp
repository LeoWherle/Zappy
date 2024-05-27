/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Action handler
*/

#include "ActionHandler.hpp"

ActionHandler::ActionHandler(std::vector<Pikmin> &pikmins, std::vector<Tile> &map, std::vector<std::string> &teams) : _pikmins(pikmins), _map(map), _teams(teams), _x(0), _y(0)
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
        {std::regex("^edi (\\d+)$"), &ActionHandler::eggDie},
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
    int x = std::atoi(arg[1].str().c_str());
    int y = std::atoi(arg[2].str().c_str());
    int index = _x * y + x;
    if (index > _x * _y || index < 0) {
        return;
    }
    std::map<Kaillou, std::size_t> tileRocks;
    for (std::size_t i = 0; i < NBKAILLOU; i++) {
        tileRocks.at(static_cast<Kaillou>(i)) = std::atoi(arg[i + 3].str().c_str());
    }
    _map[index].setRocks(tileRocks);
}

void ActionHandler::addTeamName(std::smatch &arg)
{
    std::string name = arg[1];
}

void ActionHandler::addPlayer(std::smatch &arg)
{
    std::string id = arg[1].str();
    int x = std::atoi(arg[2].str().c_str());
    int y = std::atoi(arg[3].str().c_str());
    int orientation = std::atoi(arg[4].str().c_str());
    int level = std::atoi(arg[5].str().c_str());
    std::string team = arg[6].str();

    Pikmin newPlayer(id, x, y);
    newPlayer.setDirection(orientation);
    newPlayer.setLevel(level);
    newPlayer.setTeam(team);
    _pikmins.push_back(newPlayer);
}

void ActionHandler::setPikminPosition(std::smatch &arg)
{
    std::string id = arg[1].str();
    int x = std::atoi(arg[2].str().c_str());
    int y = std::atoi(arg[3].str().c_str());
    int orientation = std::atoi(arg[4].str().c_str());

    for (auto player : _pikmins) {
        if (player == id) {
            player.setX(x);
            player.setY(y);
            player.setDirection(orientation);
        }
    }
}

void ActionHandler::setPikminLevel(std::smatch &arg)
{
    std::string id = arg[1].str();
    int x = std::atoi(arg[2].str().c_str());
    int y = std::atoi(arg[3].str().c_str());
    int orientation = std::atoi(arg[4].str().c_str());
}

void ActionHandler::setPikminInventory(std::smatch &arg)
{
    std::string id = arg[1].str();
    int x = std::atoi(arg[2].str().c_str());
    int y = std::atoi(arg[3].str().c_str());
    std::map<Kaillou, std::size_t> tileRocks;

    for (std::size_t i = 0; i < NBKAILLOU; i++) {
        tileRocks.at(static_cast<Kaillou>(i)) = std::atoi(arg[i + 4].str().c_str());
    }
    for (auto player : _pikmins) {
        if (player == id) {
            player.setX(x);
            player.setY(y);
            player.setInventory(tileRocks);
        }
    }
}

void ActionHandler::ejectPikmin(std::smatch &arg)
{
    std::string id = arg[1].str();

    for (auto player : _pikmins) {
        if (player == id) {
            player.eject();
        }
    }
}

void ActionHandler::broadcast(std::smatch &arg)
{
    std::string id = arg[1].str().c_str();
    std::string message = arg[2].str();
    return;
}

void ActionHandler::startIncantation(std::smatch &arg)
{
    int x = std::atoi(arg[1].str().c_str());
    int y = std::atoi(arg[2].str().c_str());
    std::size_t playerIndex = 0;

    while (arg.begin() + playerIndex < arg.end()) {
        std::string tmp = arg[3 + playerIndex].str();
        for (auto player : _pikmins) {
            if (player == tmp) {
                playerIndex++;
                player.startIncantation();
            }
        }
    }
}

void ActionHandler::stopIncantation(std::smatch &arg)
{
    int x = std::atoi(arg[1].str().c_str());
    int y = std::atoi(arg[2].str().c_str());
    bool result = std::atoi(arg[3].str().c_str());

    if (result == true) {
        for (auto player : _pikmins) {
            if (player.getX() == x && player.getY() == y) {
                player.levelUp();
            }
        }
        return;
    } else {
        for (auto player : _pikmins) {
            if (player.getX() == x && player.getY() == y) {
                player.failIncantation();
            }
        }
    }
}

void ActionHandler::gonnaLayEgg(std::smatch &arg)
{

}

void ActionHandler::pikminDropRessource(std::smatch &arg)
{
    std::string id = arg[1].str();
    int rock = std::atoi(arg[2].str().c_str());

    for (auto player : _pikmins) {
        if (player == id) {
            std::size_t x = player.getX();
            std::size_t y = player.getY();
            std::size_t index = y * _x + x;
            if (index > _x * _y) {
                return;
            }
            player.dropRock(static_cast<Kaillou>(rock));
            _map[index].removeRock(static_cast<Kaillou>(rock));
        }
    }
}

void ActionHandler::pikminPickRessource(std::smatch &arg)
{
    std::string id = arg[1].str();
    int rock = std::atoi(arg[2].str().c_str());

    for (auto player : _pikmins) {
        if (player == id) {
            std::size_t x = player.getX();
            std::size_t y = player.getY();
            std::size_t index = y * _x + x;
            if (index > _x * _y) {
                return;
            }
            player.dropRock(static_cast<Kaillou>(rock));
            _map[index].addRock(static_cast<Kaillou>(rock));
        }
    }
}

void ActionHandler::pikminDie(std::smatch &arg)
{

}

void ActionHandler::layedEgg(std::smatch &arg)
{

}

void ActionHandler::eggHatche(std::smatch &arg)
{

}

void ActionHandler::eggDie(std::smatch &arg)
{

}

