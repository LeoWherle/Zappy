#include <raylib-cpp.hpp>

#include "raylib-cpp.hpp"
#include "Client.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main_test_serv_comm(int ac, char **av)
{
    if (ac < 3) {
        return 84;
    }
    bool run = true;
    std::string ip = av[1];
    std::size_t port = atoi(av[2]);
    connection::Client conn(1000000, ip, port);
    ReadBuffer stdInput;
    ReadBuffer in;
    WriteBuffer StdOutput;
    WriteBuffer out;

    while (run) {
        conn.handleSelect(in, out, stdInput, StdOutput);
        std::vector<std::uint8_t> stdinBuff = stdInput.buffer();
        std::vector<std::uint8_t> inBuff = in.buffer();
        int consummed = 0;
        std::vector<std::uint8_t> tmp;
        if (stdinBuff.size() > 0) {
            std::vector<std::uint8_t> tmp = {'p', 'i', 'n', 'g'};
            if (stdinBuff == tmp) {
                out.write_to_buffer("ping");
            }
            std::vector<std::uint8_t> tmp = {'e', 'x', 'i', 't'};
            if (stdinBuff == tmp) {
                run = false;
            }
            stdInput.consume(stdinBuff.size());
        }
        if (inBuff.size() > 0) {
            tmp = {'p', 'o', 'n', 'g'};
            if (inBuff == tmp) {
                StdOutput.write_to_buffer("Pong !");
            }
            in.consume(inBuff.size());
        }
    }
    return 0;
}

int main() {
    // Initialization
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Raylib C++ Starter Kit Example");

    SetTargetFPS(60);

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // TODO: Update your variables here

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        textColor.DrawText("Congrats! You created your first window!", 190, 200, 20);
        EndDrawing();
    }

    return 0;
}
