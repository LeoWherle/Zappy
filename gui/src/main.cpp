#include "Pikmin.hpp"
#include "raylib-cpp.hpp"
#include "Communication/Client.hpp"
#include "raylib.h"
#include "Warudo.hpp"
#include "raylib.h"

int main_graphic() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 30.0f, 30.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Pikmin pikmin("yes", 0, 0);
    pikmin.setModel(ModelBank::get("RedPikmin"));
    pikmin.setTop(ModelBank::get("LeafTop"));

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_SPACE)) {
            pikmin.animationUpdate(0);
        }

        if (IsKeyPressed(KEY_C)) {
            pikmin.levelUp();
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawGrid(20, 1.0f);

                pikmin.drawModel(0);

            EndMode3D();

            std::string level = "Lvl " + std::to_string(pikmin.getLevel());
            DrawText("P I K M I N", 10, 40, 20, DARKGRAY);
            DrawText(level.c_str(), 400, 400, 50, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}


int main(int ac, char **av)
{
    //return main_graphic();
    // if (ac < 3) {
    //     return 84;
    // }
    // bool run = true;
    // std::string ip = av[1];
    // std::size_t port = atoi(av[2]);
    // connection::Client conn(100000, ip, port);
    // conn.setUpConnection();
    // ReadBuffer stdInput;
    // ReadBuffer in;
    // WriteBuffer StdOutput;
    // WriteBuffer out;

    // while (run) {
    //     conn.handleSelect(in, out, stdInput, StdOutput);
    //     std::string stdinBuff = stdInput.buffer();
    //     std::string inBuff = in.buffer();
    //     int consummed = 0;
    //     std::vector<std::uint8_t> tmp;
    //     if (stdinBuff.size() > 0) {
    //         if (stdinBuff == "GRAPHIC\n") {
    //             out.write_to_buffer(stdinBuff);
    //         }
    //         if (stdinBuff == "msz\n") {
    //             out.write_to_buffer(stdinBuff);
    //         }
    //         if (stdinBuff == "exit\n") {
    //             run = false;
    //         }
    //         stdInput.consume(stdinBuff.size());
    //     }
    //     if (inBuff.size() > 0) {
    //         StdOutput.write_to_buffer("SERVER: ");
    //         StdOutput.write_to_buffer(inBuff);
    //         in.consume(inBuff.size());
    //     }
    // }
    // return 0;
    if (ac < 3) {
        std::cerr << "Bad input (./zappy_gui ip port)" << std::endl;
        return 84;
    }
    std::string adress = av[1];
    std::size_t port = std::atoi(av[2]);
    Warudo warudo(100, adress, port);
    warudo.setUp();
    warudo.loop();
    return 0;
}
