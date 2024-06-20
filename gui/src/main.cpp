/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "InputParser.hpp"
#include "Warudo.hpp"

int main(int ac, char **av)
{
    InputParser input(ac, av);
    try {
        input.parseMandatory();
    } catch (const InputParser::ParseError &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    input.parseOption();
    GUI::Warudo warudo(100, input);
    warudo.setUp();
    warudo.loop();
    return 0;
}