/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "InputParser.hpp"
#include "Warudo.hpp"
#include "ModelBank.hpp"
#include "TextureBank.hpp"

int buildWorld(InputParser &in)
{
    GUI::Warudo warudo(100, in);
    try {
        warudo.setUp();
    } catch (const std::exception &e) {
        std::cerr << "Can't connect to server" << std::endl;
        return 84;
    }
    warudo.loop();
    return 0;
}

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
    int ret = buildWorld(input);
    GUI::ModelBank::reset();
    GUI::TextureBank::reset();
    CloseWindow();
    return ret;
}
