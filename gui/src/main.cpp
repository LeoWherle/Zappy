#include "Pikmin.hpp"
#include "raylib-cpp.hpp"
#include "Communication/Client.hpp"
#include "raylib.h"
#include "Warudo.hpp"
#include "raylib.h"

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cerr << "Bad input (./zappy_gui ip port)" << std::endl;
        return 84;
    }
    std::string adress = av[1];
    std::size_t port = std::atoi(av[2]);
    GUI::Warudo warudo(100, adress, port);
    warudo.setUp();
    warudo.loop();
    return 0;
}
