#include "Communication/Client.hpp"
#include "Pikmin.hpp"
#include "Warudo.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"

int main_graphic()
{
    // const int screenWidth = 800;
    // const int screenHeight = 450;
    //
    // InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");
    //
    //// Define the camera to look into our 3d world
    // Camera3D camera = { 0 };
    // camera.position = (Vector3){ 0.0f, 30.0f, 30.0f };  // Camera position
    // camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    // camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    // camera.fovy = 45.0f;                                // Camera field-of-view Y
    // camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
    //
    // Pikmin pikmin("yes", 0, 0);
    // pikmin.setModel(ModelBank::get("RedPikmin"));
    // pikmin.setTop(ModelBank::get("LeafTop"));
    //
    // SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // while (!WindowShouldClose())    // Detect window close button or ESC key
    //{
    //    if (IsKeyDown(KEY_SPACE)) {
    //        pikmin.animationUpdate(0);
    //    }
    //
    //    if (IsKeyPressed(KEY_C)) {
    //        pikmin.levelUp();
    //    }
    //    BeginDrawing();
    //
    //        ClearBackground(RAYWHITE);
    //
    //        BeginMode3D(camera);
    //
    //            DrawGrid(20, 1.0f);
    //
    //            pikmin.drawModel(0);
    //
    //        EndMode3D();
    //
    //        std::string level = "Lvl " + std::to_string(pikmin.getLevel());
    //        DrawText("P I K M I N", 10, 40, 20, DARKGRAY);
    //        DrawText(level.c_str(), 400, 400, 50, DARKGRAY);
    //
    //        DrawFPS(10, 10);
    //
    //    EndDrawing();
    //}
    // CloseWindow();
    // return 0;
}

#include "raygui.h"
#include "raylib.h"
#include "styles/style_sunny.h"

static Vector2 window_position = {10, 10};
static Vector2 window_size = {200, 400};
static bool minimized = false;
static bool moving = false;
static bool resizing = false;
static Vector2 scroll;

static Vector2 window2_position = {250, 10};
static Vector2 window2_size = {200, 400};
static bool minimized2 = false;
static bool moving2 = false;
static bool resizing2 = false;
static Vector2 scroll2;

void GuiWindowFloating(
    Vector2 *position, Vector2 *size, bool *minimized, bool *moving, bool *resizing,
    void (*draw_content)(Vector2, Vector2), Vector2 content_size, Vector2 *scroll, const char *title
)
{
#if !defined(RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT)
#define RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT 24
#endif

#if !defined(RAYGUI_WINDOW_CLOSEBUTTON_SIZE)
#define RAYGUI_WINDOW_CLOSEBUTTON_SIZE 18
#endif

    int close_title_size_delta_half =
        (RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT - RAYGUI_WINDOW_CLOSEBUTTON_SIZE) / 2;

    // window movement and resize input and collision check
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !*moving && !*resizing) {
        Vector2 mouse_position = GetMousePosition();

        Rectangle title_collision_rect = {
            position->x, position->y,
            size->x - (RAYGUI_WINDOW_CLOSEBUTTON_SIZE + close_title_size_delta_half),
            RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT
        };
        Rectangle resize_collision_rect = {position->x + size->x - 20, position->y + size->y - 20, 20, 20};

        if (CheckCollisionPointRec(mouse_position, title_collision_rect)) {
            *moving = true;
        } else if (!*minimized && CheckCollisionPointRec(mouse_position, resize_collision_rect)) {
            *resizing = true;
        }
    }

    // window movement and resize update
    if (*moving) {
        Vector2 mouse_delta = GetMouseDelta();
        position->x += mouse_delta.x;
        position->y += mouse_delta.y;

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            *moving = false;

            // clamp window position keep it inside the application area
            if (position->x < 0)
                position->x = 0;
            else if (position->x > GetScreenWidth() - size->x)
                position->x = GetScreenWidth() - size->x;
            if (position->y < 0)
                position->y = 0;
            else if (position->y > GetScreenHeight())
                position->y = GetScreenHeight() - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT;
        }

    } else if (*resizing) {
        Vector2 mouse = GetMousePosition();
        if (mouse.x > position->x)
            size->x = mouse.x - position->x;
        if (mouse.y > position->y)
            size->y = mouse.y - position->y;

        // clamp window size to an arbitrary minimum value and the window size as the maximum
        if (size->x < 100)
            size->x = 100;
        else if (size->x > GetScreenWidth())
            size->x = GetScreenWidth();
        if (size->y < 100)
            size->y = 100;
        else if (size->y > GetScreenHeight())
            size->y = GetScreenHeight();

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            *resizing = false;
        }
    }

    // window and content drawing with scissor and scroll area
    if (*minimized) {
        GuiStatusBar(
            (Rectangle) {position->x, position->y, size->x, RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT}, title
        );

        if (GuiButton(
                (Rectangle
                ) {position->x + size->x - RAYGUI_WINDOW_CLOSEBUTTON_SIZE - close_title_size_delta_half,
                   position->y + close_title_size_delta_half, RAYGUI_WINDOW_CLOSEBUTTON_SIZE,
                   RAYGUI_WINDOW_CLOSEBUTTON_SIZE},
                "#120#"
            )) {
            *minimized = false;
        }

    } else {
        *minimized = GuiWindowBox((Rectangle) {position->x, position->y, size->x, size->y}, title);

        // scissor and draw content within a scroll panel
        if (draw_content != NULL) {
            Rectangle scissor = {0};
            GuiScrollPanel(
                (Rectangle
                ) {position->x, position->y + RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT, size->x,
                   size->y - RAYGUI_WINDOWBOX_STATUSBAR_HEIGHT},
                NULL, (Rectangle) {position->x, position->y, content_size.x, content_size.y}, scroll, &scissor
            );

            bool require_scissor = size->x < content_size.x || size->y < content_size.y;

            if (require_scissor) {
                BeginScissorMode(scissor.x, scissor.y, scissor.width, scissor.height);
            }

            draw_content(*position, *scroll);

            if (require_scissor) {
                EndScissorMode();
            }
        }

        // draw the resize button/icon
        GuiDrawIcon(71, position->x + size->x - 20, position->y + size->y - 20, 1, WHITE);
    }
}

static void DrawContent(Vector2 position, Vector2 scroll)
{
    GuiButton((Rectangle) {position.x + 20 + scroll.x, position.y + 50 + scroll.y, 100, 25}, "Button 1");
    GuiButton((Rectangle) {position.x + 20 + scroll.x, position.y + 100 + scroll.y, 100, 25}, "Button 2");
    GuiButton((Rectangle) {position.x + 20 + scroll.x, position.y + 150 + scroll.y, 100, 25}, "Button 3");
    GuiLabel((Rectangle) {position.x + 20 + scroll.x, position.y + 200 + scroll.y, 250, 25}, "A Label");
    GuiLabel((Rectangle) {position.x + 20 + scroll.x, position.y + 250 + scroll.y, 250, 25}, "Another Label");
    GuiLabel(
        (Rectangle) {position.x + 20 + scroll.x, position.y + 300 + scroll.y, 250, 25}, "Yet Another Label"
    );
}

int raygui_main(void)
{
    InitWindow(960, 560, "raygui - floating window example");
    SetTargetFPS(60);
    GuiLoadStyleSunny();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        GuiWindowFloating(
            &window_position, &window_size, &minimized, &moving, &resizing, &DrawContent,
            (Vector2) {140, 320}, &scroll, "Movable & Scalable Window"
        );
        GuiWindowFloating(
            &window2_position, &window2_size, &minimized2, &moving2, &resizing2, &DrawContent,
            (Vector2) {140, 320}, &scroll2, "Another window"
        );
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

int main(int ac, char **av)
{
    return raygui_main();
    // return main_graphic();
    //  if (ac < 3) {
    //      return 84;
    //  }
    //  bool run = true;
    //  std::string ip = av[1];
    //  std::size_t port = atoi(av[2]);
    //  connection::Client conn(100000, ip, port);
    //  conn.setUpConnection();
    //  ReadBuffer stdInput;
    //  ReadBuffer in;
    //  WriteBuffer StdOutput;
    //  WriteBuffer out;

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
    GUI::Warudo warudo(100, adress, port);
    warudo.setUp();
    warudo.loop();
    return 0;
}
