/*******************************************************************************************
 *
 *   raylib [textures] example - MPEG video playing
 *
 *   We have two options to decode video & audio using pl_mpeg.h library:
 *
 *   1) Use plm_decode() and just hand over the delta time since the last call.
 *      It will decode everything needed and call your callbacks (specified
 *through plm_set_{video|audio}_decode_callback()) any number of times.
 *
 *   2) Use plm_decode_video() and plm_decode_audio() to decode exactly one
 *      frame of video or audio data at a time. How you handle the
 *synchronization of both streams is up to you.
 *
 *   This example uses option 2)
 *
 *   This example has been created using raylib 3.0 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h
 *for details)
 *
 *   Copyright (c) 2020 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

#include "raylib.h"

#include <cstdint>
#include <stdlib.h>

#include "Video.hpp"

int main(void)
{
    // Initialization
    //---------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - MPEG video playing");

    // AudioStream stream = {0};

    Video video("rick.mpeg");

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //-----------------------------------------------------
        if (IsKeyPressed(KEY_SPACE)) {
            video.setRunning(video.isPaused());
        }
        if (IsKeyPressed(KEY_R)) {
            video.Rewind();
        }
        if (IsKeyPressed(KEY_L)) {
            video.Loop(!video.isLooping());
        }
        video.Update();

        //-----------------------------------------------------

        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        video.Draw();

        EndDrawing();
        //-----------------------------------------------------
    }

    CloseWindow(); // Close window and OpenGL context
    //----------------------------------------------------------

    return 0;
}