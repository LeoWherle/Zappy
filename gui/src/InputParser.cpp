/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** InputParser
*/

#include <algorithm>
#include "InputParser.hpp"

InputParser::InputParser(int ac, char **av)
{
    for (std::size_t i = 0; i < ac; i++) {
        _inputs.push_back(std::string(av[i]));
    }
}

InputParser::~InputParser()
{
}

void InputParser::parseMandatory(void)
{
    auto pos = std::find(_inputs.begin(), _inputs.end(), "-p");
    if (pos >= _inputs.end() - 1) {
        throw ParseError("Inputs error\nUSAGE: ./zappy_gui -p port -h machine [--ref-serv]");
    }
    pos++;
    _port = std::stoi(*(pos));
    pos = std::find(_inputs.begin(), _inputs.end(), "-h");
    if (pos >= _inputs.end() - 1) {
        throw ParseError("Inputs error\nUSAGE: ./zappy_gui -p port -h machine [--ref-serv]");
    }
    pos++;
    _adress = *(pos);
}

void InputParser::parseOption(void)
{
    if (std::find(_inputs.begin(), _inputs.end(), "--ref-serv") != _inputs.end()) {
        _ref = true;
    } else {
        _ref = false;
    }
}

std::string InputParser::getAdress(void) const
{
    return _adress;
}

std::size_t InputParser::getPort(void) const
{
    return _port;
}

bool InputParser::getRef(void) const
{
    return _ref;
}
