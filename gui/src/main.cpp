#include "raylib-cpp.hpp"
#include "Communication/Client.hpp"
#include "raylib.h"
#include <vector>
#include "Warudo.hpp"
#include "raylib.h"

int main_graphic() {
// Initialization
    //--------------------------------------------------------------------------------------
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

    Texture2D texture = LoadTexture("gui/res/textures/RedPikmin.png"); // Load cubicmap texture
    Texture2D flowerTexture = LoadTexture("gui/res/textures/FlowerTop.png"); // Load cubicmap texture
    Texture2D budTexture = LoadTexture("gui/res/textures/BudTop.png"); // Load cubicmap texture
    Texture2D leafTexture = LoadTexture("gui/res/textures/LeafTop.png"); // Load cubicmap texture
    Texture2D leaf_normal = LoadTexture("gui/res/textures/LeafTop_N.png"); // Load cubicmap texture
    int animFrameCounter = 0;

    std::vector<Model> tops;
    int topIndex = 0;

    Model model = LoadModel("gui/res/models/RedPikmin.iqm");                 // Load OBJ model
    if (model.meshCount == 0) {
        std::cout << "Error: No mesh found" << std::endl;
        return 84;
    }
    int animationsCount = 1;
    ModelAnimation *animations = LoadModelAnimations("gui/res/models/RedPikmin.iqm", &animationsCount);
    model.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture); // Set model diffuse texture

    Model flower = LoadModel("gui/res/models/FlowerTop.iqm");
    if (flower.meshCount == 0) {
        std::cout << "Error: No mesh found" << std::endl;
        return 84;
    }
    flower.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });
    int flowerAnimationsCount = 1;
    ModelAnimation *flowerAnimations = LoadModelAnimations("gui/res/models/FlowerTop.iqm", &flowerAnimationsCount);
    SetMaterialTexture(&flower.materials[0], MATERIAL_MAP_DIFFUSE, flowerTexture); // Set model diffuse texture
    tops.push_back(flower);

    Model bud = LoadModel("gui/res/models/BudTop.iqm");
    if (bud.meshCount == 0) {
        std::cout << "Error: No mesh found" << std::endl;
        return 84;
    }
    bud.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });
    SetMaterialTexture(&bud.materials[0], MATERIAL_MAP_DIFFUSE, budTexture); // Set model diffuse texture
    int budAnimationsCount = 1;
    ModelAnimation *budAnimations = LoadModelAnimations("gui/res/models/BudTop.iqm", &budAnimationsCount);
    tops.push_back(bud);

    Model leaf = LoadModel("gui/res/models/LeafTop.iqm");
    if (leaf.meshCount == 0) {
        std::cout << "Error: No mesh found" << std::endl;
        return 84;
    }
    leaf.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });
    SetMaterialTexture(&leaf.materials[0], MATERIAL_MAP_DIFFUSE, leafTexture); // Set model diffuse texture
    SetMaterialTexture(&leaf.materials[0], MATERIAL_MAP_NORMAL, leaf_normal); // Set model diffuse texture
    int leafAnimationsCount = 1;
    ModelAnimation *leafAnimations = LoadModelAnimations("gui/res/models/LeafTop.iqm", &leafAnimationsCount);
    tops.push_back(leaf);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //UpdateCamera(&camera, CAMERA_FREE);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // if (IsKeyPressed(KEY_D))
            //     cubePosition.x += 1.0f;
            // if (IsKeyPressed(KEY_A))
            //     cubePosition.x -= 1.0f;
            // if (IsKeyPressed(KEY_W))
            //     cubePosition.z -= 1.0f;
            // if (IsKeyPressed(KEY_S))
            //     cubePosition.z += 1.0f;
            if (IsKeyDown(KEY_SPACE)) {
                UpdateModelAnimation(model, animations[0], animFrameCounter);
                UpdateModelAnimation(flower, flowerAnimations[0], animFrameCounter);
                UpdateModelAnimation(bud, budAnimations[0], animFrameCounter);
                UpdateModelAnimation(leaf, leafAnimations[0], animFrameCounter);
                animFrameCounter++;
                if (animFrameCounter >= animations[0].frameCount) animFrameCounter = 0;
            }

            if (IsKeyPressed(KEY_C)) {
                topIndex++;
                if (topIndex >= tops.size()) topIndex = 0;
            }

            BeginMode3D(camera);


                DrawGrid(20, 1.0f);

                DrawModel(model, (Vector3){ 0.0f, 0.0f, 0.0f }, 0.5, WHITE);   // Draw 3d model with texture
                DrawModel(tops[topIndex], (Vector3){ 0.0f, 0.0f, 0.0f }, 0.5, ORANGE);   // Draw 3d model with texture

            EndMode3D();

            DrawText("P I K M I N", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


int main(int ac, char **av)
{
    return main_graphic();
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
