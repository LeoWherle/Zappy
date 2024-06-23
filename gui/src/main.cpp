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
    bool failed = false;
    try {
        input.parseMandatory();
    } catch (const InputParser::ParseError &e) {
        std::cout << e.what() << std::endl;
        failed = true;
    } catch (const std::exception &e) {
        failed = true;
    }
    if (ac < 3 || failed) {
        std::cerr << "Bad input (./zappy_gui -p port -h ip)" << std::endl;
        return 84;
    }
    input.parseOption();
    GUI::Warudo warudo(100, input);
    try {
        warudo.setUp();
    } catch (const std::exception &e) {
        std::cerr << "Can't connect to server" << std::endl;
        return 84;
    }
    warudo.loop();
    return 0;
}
