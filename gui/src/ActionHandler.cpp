/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Action handler
*/

#include "ActionHandler.hpp"
#include <iostream>

namespace GUI {
    ActionHandler::ActionHandler(std::vector<Pikmin> &pikmins, std::vector<Tile> &map,
        std::vector<Team> &teams, std::pair<std::size_t, std::size_t> &size,
        float &timeMult, GuiCamera &cam, WorldCamera &worldCam):
        _pikmins(pikmins), _map(map), _teams(teams), _x(size.first), _y(size.second), _guiCam(cam), _timeMult(timeMult), _worldCam(worldCam)
    {
        std::srand(std::time(nullptr));
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
            {std::regex("^pex (\\d+)$"), &ActionHandler::ejectPikmin},
            {std::regex("^pbc (\\d+) ([^\\n]+)$"), &ActionHandler::broadcast},
            {std::regex("^pic (\\d+) (\\d+) (\\d+) ((?:\\d+ )*\\d+)$"), &ActionHandler::startIncantation},
            {std::regex("^pie (\\d+) (\\d+) (\\d+)$"), &ActionHandler::stopIncantation},
            {std::regex("^pfk (\\d+)$"), &ActionHandler::gonnaLayEgg},
            {std::regex("^pdr (\\d+) (\\d+)$"), &ActionHandler::pikminDropRessource},
            {std::regex("^pgt (\\d+) (\\d+)$"), &ActionHandler::pikminPickRessource},
            {std::regex("^pdi (\\d+)$"), &ActionHandler::pikminDie},
            {std::regex("^enw (\\d+) (\\d+) (\\d+) (\\d+)$"), &ActionHandler::layedEgg},
            {std::regex("^ebo (\\d+)$"), &ActionHandler::eggHatche},
            {std::regex("^edi (\\d+)$"), &ActionHandler::pikminDie},
            {std::regex("^sgt (\\d+(?:.\\d+)?)$"), &ActionHandler::setTimeMult},
            {std::regex("^sst (\\d+(?:.\\d+)?)$"), &ActionHandler::setTimeMult},
            {std::regex("^pm (\\d+) (\\d+) (\\d+)$"), &ActionHandler::pikminMoving},
            {std::regex("^ptr (\\d+)$"), &ActionHandler::pikminTurningRight},
            {std::regex("^ptl (\\d+)$"), &ActionHandler::pikminTurningLeft},
            {std::regex("^pla (\\d+)$"), &ActionHandler::pikminLookingAround},
            {std::regex("^pf (\\d+)$"), &ActionHandler::pikminForking},
            {std::regex("^pto (\\d+) (\\d+)$"), &ActionHandler::pikminTakeObject},
            {std::regex("^pdo (\\d+) (\\d+)$"), &ActionHandler::pikminDropObject},
            {std::regex("^ppx (\\d+)$"), &ActionHandler::pikminEject}
        });
        _nbTeam = 0;

        std::vector<ModelType> possibleModel({
            RED_PIKMIN,
            YELLOW_PIKMIN,
            BLUE_PIKMIN,
            PURPLE_PIKMIN,
            WHITE_PIKMIN,
            ROCK_PIKMIN,
            WING_PIKMIN,
            ICE_PIKMIN,
            SPECTRAL_PIKMIN
        });

        while (!possibleModel.empty()) {
            std::size_t idx = std::rand() % possibleModel.size();

            _pikminModels.push_back(possibleModel[idx]);
            possibleModel.erase(possibleModel.begin() + idx);
        }

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
        std::cerr << "failed packet: " << action << std::endl;
        return false;
    }

    void ActionHandler::setmapSize(std::smatch &arg)
    {
        _x = std::stoi(arg[1].str());
        _y = std::stoi(arg[2].str());
        _map.clear();
        for (std::size_t i = 0; i < _x; i++) {
            for (std::size_t j = 0; j < _y; j++) {
                _map.push_back(Tile(i, j));
                _map[_map.size() - 1].getRockModel();
            }
        }
        _worldCam.setUpCam(_x, _y);
    }

    void ActionHandler::setTileContent(std::smatch &arg)
    {
        int x = std::stoi(arg[1].str());
        int y = std::stoi(arg[2].str());
        std::size_t index = x * _y + y;
        if (index > _x * _y) {
            return;
        }
        std::map<Kaillou, std::size_t> tileRocks;
        for (std::size_t i = 0; i < NBKAILLOU; i++) {
            tileRocks.insert(std::pair<Kaillou, std::size_t>((static_cast<Kaillou>(i)), std::stoi(arg[i + 3].str())));
        }
        _map[index].setRocks(tileRocks);
    }

    static const std::vector<raylib::Color> colors({
        raylib::Color::White(),
        raylib::Color::DarkPurple(),
        raylib::Color::Green(),
        raylib::Color::DarkBlue(),
        raylib::Color::DarkGray(),
        raylib::Color::Purple(),
        raylib::Color::Magenta(),
        raylib::Color::Maroon(),
        raylib::Color::Beige(),
        raylib::Color::Brown(),
        raylib::Color::Black(),
    });

    void ActionHandler::addTeamName(std::smatch &arg)
    {
        std::string name;
        std::shared_ptr<GuiModel> model;
        raylib::Color color;
        std::size_t modelIndex = 0;
        std::size_t colorIndex = 0;

        name = arg[1];
        modelIndex = _nbTeam % _pikminModels.size();
        colorIndex = (_nbTeam - modelIndex) % colors.size();
        model = ModelBank::get(_pikminModels[modelIndex]);
        color = colors[colorIndex];
        _nbTeam++;

        Team team(name, model, color);

        _teams.emplace_back(team);
    }

    void ActionHandler::addPlayer(std::smatch &arg)
    {
        std::string id = arg[1].str();
        int x = std::stoi(arg[2].str());
        int y = std::stoi(arg[3].str());
        int orientation = std::stoi(arg[4].str());
        int level = std::stoi(arg[5].str());
        std::string teamName = arg[6].str();

        for (auto &player : _pikmins) {
            if (player == id) {
                for (auto &team : _teams) {
                    if (team == teamName) {
                        player.setTeam(team);
                        player.spawnAsPikmin();
                        player.updatePosition(x, y, orientation);
                        player.updateLevel(level);
                    }
                }
                return;
            }
        }

        Pikmin newPikmin(id, x, y, _x, _y);
        for (auto &team : _teams) {
            if (team == teamName) {
                newPikmin.setTeam(team);
                newPikmin.spawnAsPikmin();
                newPikmin.updatePosition(x, y, orientation);
                newPikmin.updateLevel(level);
                _pikmins.emplace_back(newPikmin);
            }
        }
    }

    void ActionHandler::setPikminPosition(std::smatch &arg)
    {
        std::string id = arg[1].str();
        int x = std::stoi(arg[2].str());
        int y = std::stoi(arg[3].str());
        int orientation = std::stoi(arg[4].str());

        for (auto &player : _pikmins) {
            if (player == id) {
                player.updatePosition(x, y, orientation);
            }
        }
    }

    void ActionHandler::setPikminLevel(std::smatch &arg)
    {
        std::string id = arg[1].str();
        int level = std::stoi(arg[2].str());

        for (auto &player : _pikmins) {
            if (player == id) {
                player.updateLevel(level);
            }
        }
    }

    void ActionHandler::setPikminInventory(std::smatch &arg)
    {
        std::string id = arg[1].str();
        std::map<Kaillou, std::size_t> tileRocks;

        for (std::size_t i = 0; i < NBKAILLOU; i++) {
            tileRocks.insert(std::pair<Kaillou, std::size_t>((static_cast<Kaillou>(i)), std::stoi(arg[i + 4].str())));
        }
        for (auto &player : _pikmins) {
            if (player == id) {
                player.updateInventory(tileRocks);
            }
        }
    }

    void ActionHandler::ejectPikmin(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &player : _pikmins) {
            if (player == id) {
                player.eject();
            }
        }
    }

    void ActionHandler::broadcast(std::smatch &arg)
    {
        std::string id = arg[1].str();
        std::string message = arg[2].str();

        for (auto &player : _pikmins) {
            if (player == id) {
                player.broadcast();
                _guiCam.addMessage(message, player);
            }
        }
    }

    void ActionHandler::startIncantation(std::smatch &arg)
    {
        //int x = std::stoi(arg[1].str());
        //int y = std::stoi(arg[2].str());
        std::string incanters = arg[4].str();

        while (incanters.size() > 0) {
            std::string tmp = incanters.substr(0, incanters.find(' '));
            for (auto &player : _pikmins) {
                if (player == tmp) {
                    player.startIncant();
                }
            }
            std::size_t index = incanters.find(' ');
            if (index == std::string::npos) {
                incanters.erase();
            } else {
                incanters.erase(0, index + 1);
            }
        }
    }

    void ActionHandler::stopIncantation(std::smatch &arg)
    {
        int x = std::stoi(arg[1].str());
        int y = std::stoi(arg[2].str());
        bool result = std::stoi(arg[3].str());

        for (auto &player : _pikmins) {
            if (player.isOnTile(x, y)) {
                player.stopIncant(result);
            }
        }
    }

    void ActionHandler::gonnaLayEgg(std::smatch &arg)
    {
        std::string pikminId = arg[1].str();

        for (auto &player : _pikmins) {
            if (player == pikminId) {
                player.LayingEgg();
            }
        }
    }

    void ActionHandler::pikminDropRessource(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &player : _pikmins) {
            if (player == id) {
                player.dropRock();
            }
        }
    }

    void ActionHandler::pikminPickRessource(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &player : _pikmins) {
            if (player == id) {
                player.pickRock();
            }
        }
    }

    void ActionHandler::pikminDie(std::smatch &arg)
    {
        std::string pikminId = arg[1].str();

        for (std::size_t i = 0; i < _pikmins.size(); i++) {
            if (_pikmins[i] == pikminId) {
                _pikmins[i].die();
            }
        }
    }

    void ActionHandler::layedEgg(std::smatch &arg)
    {
        std::string eggId = arg[1].str();
        std::string pikminId = arg[2].str();
        std::size_t x = std::stoi(arg[3].str());
        std::size_t y = std::stoi(arg[4].str());
        Pikmin newPikmin(eggId, x, y, _x, _y);

        newPikmin.spawnAsEgg();
        _pikmins.emplace_back(newPikmin);
    }

    void ActionHandler::eggHatche(std::smatch &arg)
    {
        std::string eggId = arg[1].str();

        for (std::size_t i = 0; i < _pikmins.size(); i++) {
            if (_pikmins[i] == eggId && _pikmins[i].getStatus() == Pikmin::State::EGG) {
                _pikmins.erase(_pikmins.begin() + i);
            }
        }
    }

    void ActionHandler::setTimeMult(std::smatch &arg)
    {
        float newMult = std::stof(arg[1].str());

        if (arg[0].str().find("sgt") != std::string::npos) {
            _guiCam.setTime(newMult);
        }
        _timeMult = newMult;
    }

    void ActionHandler::pikminMoving(std::smatch &arg)
    {
        std::string id = arg[1].str();
        std::size_t x = std::stoi(arg[2].str());
        std::size_t y = std::stoi(arg[3].str());

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.move(x, y);
            }
        }
    }

    void ActionHandler::pikminTurningRight(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.turnRight();
            }
        }
    }

    void ActionHandler::pikminTurningLeft(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.turnLeft();
            }
        }
    }

    void ActionHandler::pikminLookingAround(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.look();
            }
        }
    }

    void ActionHandler::pikminForking(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.fork();
            }
        }
    }

    void ActionHandler::pikminTakeObject(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.pickRock();
            }
        }
    }

    void ActionHandler::pikminDropObject(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.dropRock();
            }
        }
    }

    void ActionHandler::pikminEject(std::smatch &arg)
    {
        std::string id = arg[1].str();

        for (auto &pikmin : _pikmins) {
            if (pikmin == id) {
                pikmin.ejecting();
            }
        }
    }
}