#include "Pikmin.hpp"
#include "raylib-cpp.hpp"
#include "Communication/Client.hpp"
#include "raylib.h"
#include "Warudo.hpp"
#include "raylib.h"
#include "InputParser.hpp"

int main(int ac, char **av)
{
    InputParser input(ac, av);
    try {
        input.parseMandatory();
    } catch (InputParser::ParseError const &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    input.parseOption();
    GUI::Warudo warudo(100, input);
    warudo.setUp();
    warudo.loop();
    return 0;
}
