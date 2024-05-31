/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Action handler
*/

#include "ActionHandler.hpp"

ActionHandler::ActionHandler(std::vector<Pikmin> &pikmins, std::vector<Tile> &map, std::vector<std::string> &teams, std::pair<std::size_t, std::size_t> &size, float &timeMult):
    _pikmins(pikmins), _map(map), _teams(teams), _x(size.first), _y(size.second), _timeMult(timeMult)
{
    _x = 0;
    _y = 0;
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
        {std::regex("^pic (\\d+) (\\d+) (\\d+) ((?:\\d+ )*\\d+)$"), &ActionHandler::startIncantation},
        {std::regex("^pie (\\d+) (\\d+) (\\d+)$"), &ActionHandler::stopIncantation},
        {std::regex("^pfk (\\d+)$"), &ActionHandler::gonnaLayEgg},
        {std::regex("^pdr (\\d+) i$"), &ActionHandler::pikminDropRessource},
        {std::regex("^pgt (\\d+) i$"), &ActionHandler::pikminPickRessource},
        {std::regex("^pdi (\\d+)$"), &ActionHandler::pikminDie},
        {std::regex("^enw (\\d+) (\\d+) (\\d+) (\\d+)$"), &ActionHandler::layedEgg},
        {std::regex("^ebo (\\d+)$"), &ActionHandler::eggHatche},
        {std::regex("^edi (\\d+)$"), &ActionHandler::pikminDie},
        {std::regex("^sgt (\\d+(?:.\\d+)?)$"), &ActionHandler::setTimeMult},
    });
}

ActionHandler::~ActionHandler()
{
}

bool ActionHandler::operator()(std::string &action)
{
    for (auto &[regex, reaction] : _regexMap) {
        std::smatch match;
        if (std::regex_match(action, match, regex)) {
            (this->*reaction)(match);
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
        tileRocks.insert(std::pair<Kaillou, std::size_t>((static_cast<Kaillou>(i)), std::atoi(arg[i + 3].str().c_str())));
    }
    _map[index].setRocks(tileRocks);
}

void ActionHandler::addTeamName(std::smatch &arg)
{
    std::string name = arg[1];

    _teams.push_back(name);
}

void ActionHandler::addPlayer(std::smatch &arg)
{
    std::string id = arg[1].str();
    int x = std::atoi(arg[2].str().c_str());
    int y = std::atoi(arg[3].str().c_str());
    int orientation = std::atoi(arg[4].str().c_str());
    int level = std::atoi(arg[5].str().c_str());
    std::string team = arg[6].str();
}

void ActionHandler::setPikminPosition(std::smatch &arg)
{
    std::string id = arg[1].str();
    int x = std::atoi(arg[2].str().c_str());
    int y = std::atoi(arg[3].str().c_str());
    int orientation = std::atoi(arg[4].str().c_str());

    for (auto &player : _pikmins) {
        if (player == id) {
            if ((player.getX() != x || player.getY() != y) && player.getStatus() != Pikmin::State::EJECT) {
                player.setPositionVector(raylib::Vector3(player.getX(), 0, player.getY()));
                player.setAnimation(_animation.get("walk"));
                player.setMotionVector(raylib::Vector3(player.getX() - x, 0, player.getY() - y));
            }
            player.setX(x);
            player.setY(y);
            player.setDirection(orientation);
            player.setRotation(90 * orientation);
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
        tileRocks.insert(std::pair<Kaillou, std::size_t>((static_cast<Kaillou>(i)), std::atoi(arg[i + 4].str().c_str())));
    }
    for (auto &player : _pikmins) {
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

    for (auto &player : _pikmins) {
        if (player == id) {
            player.setAnimation(_animation.get("eject"));
            player.setStatus(Pikmin::State::EJECT);
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
    std::string incanters = arg[3].str();

    while (incanters.size() > 0) {
        std::string tmp = incanters.substr(0, incanters.find(' ') - 1);
        for (auto &player : _pikmins) {
            if (player == tmp) {
                player.setAnimation(_animation.get("incant"));
            }
        }
        std::size_t index = incanters.find(' ') + 1;
        if (index > incanters.size())
            index = incanters.size();
        incanters = incanters.substr(index);
    }
}

void ActionHandler::stopIncantation(std::smatch &arg)
{
    int x = std::atoi(arg[1].str().c_str());
    int y = std::atoi(arg[2].str().c_str());
    bool result = std::atoi(arg[3].str().c_str());

    if (result == true) {
        for (auto &player : _pikmins) {
            if (player.getX() == x && player.getY() == y) {
                player.levelUp();
                player.setAnimation(_animation.get("level up"));
            }
        }
        return;
    } else {
        for (auto &player : _pikmins) {
            if (player.getX() == x && player.getY() == y) {
                player.setAnimation(_animation.get("failure"));
            }
        }
    }
}

void ActionHandler::gonnaLayEgg(std::smatch &arg)
{
    std::string pikminId = arg[1].str();

    for (auto &player : _pikmins) {
        if (player == pikminId) {
            player.setAnimation(_animation.get("laying egg"));
        }
    }
}

void ActionHandler::pikminDropRessource(std::smatch &arg)
{
    std::string id = arg[1].str();
    int rock = std::atoi(arg[2].str().c_str());

    for (auto &player : _pikmins) {
        if (player == id) {
            std::size_t x = player.getX();
            std::size_t y = player.getY();
            std::size_t index = y * _x + x;
            if (index > _x * _y) {
                return;
            }
            player.dropRock(static_cast<Kaillou>(rock));
            _map[index].addRock(static_cast<Kaillou>(rock));
            player.setAnimation(_animation.get("drop ressource"));
        }
    }
}

void ActionHandler::pikminPickRessource(std::smatch &arg)
{
    std::string id = arg[1].str();
    int rock = std::atoi(arg[2].str().c_str());

    for (auto &player : _pikmins) {
        if (player == id) {
            std::size_t x = player.getX();
            std::size_t y = player.getY();
            std::size_t index = y * _x + x;
            if (index > _x * _y) {
                return;
            }
            player.pickRock(static_cast<Kaillou>(rock));
            _map[index].removeRock(static_cast<Kaillou>(rock));
        }
    }
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
    _pikmins[_pikmins.size() - 1].setStatus(Pikmin::State::EGG);
    _pikmins[_pikmins.size() - 1].setModel(_model.get("egg"));
    _pikmins[_pikmins.size() - 1].setAnimation(_animation.get("egg"));
}

void ActionHandler::eggHatche(std::smatch &arg)
{
    std::string eggId = arg[1].str();

    raylib::Color red = raylib::Color::Red();
    for (std::size_t i = 0; i < _pikmins.size(); i++) {
        if (_pikmins[i] == eggId) {
            _pikmins[i].setModel(_model.get("pikmin"));
            _pikmins[i].setAnimation(_animation.get("birth"));
            _pikmins[i].setStatus(Pikmin::State::ALIVE);
            _pikmins[i].setColor(red);
        }
    }
}

void ActionHandler::setTimeMult(std::smatch &arg)
{
    float newMult = std::atof(arg[1].str().c_str());

    _timeMult = newMult;
}
