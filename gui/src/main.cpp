#include <raylib-cpp.hpp>
#include <sstream>

#include "raylib-cpp.hpp"
#include "Communication/Client.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int ac, char **av)
{
    if (ac < 3) {
        return 84;
    }
    bool run = true;
    std::string ip = av[1];
    std::size_t port = atoi(av[2]);
    connection::Client conn(100000, ip, port);
    conn.setUpConnection();
    ReadBuffer stdInput;
    ReadBuffer in;
    WriteBuffer StdOutput;
    WriteBuffer out;

    while (run) {
        conn.handleSelect(in, out, stdInput, StdOutput);
        std::string stdinBuff = stdInput.buffer();
        std::string inBuff = in.buffer();
        int consummed = 0;
        std::vector<std::uint8_t> tmp;
        if (stdinBuff.size() > 0) {
            if (stdinBuff == "GRAPHIC\n") {
                out.write_to_buffer(stdinBuff);
            }
            if (stdinBuff == "msz\n") {
                out.write_to_buffer(stdinBuff);
            }
            if (stdinBuff == "exit\n") {
                run = false;
            }
            stdInput.consume(stdinBuff.size());
        }
        if (inBuff.size() > 0) {
            StdOutput.write_to_buffer("SERVER: ");
            StdOutput.write_to_buffer(inBuff);
            in.consume(inBuff.size());
        }
    }
    return 0;
}

int main_1() {
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
