/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** Video
*/

#pragma once

#include <memory>
#include <string.h>
#include <string>

#include "pl_mpeg.h"

#include "Image.hpp"
#include "Texture.hpp"

namespace GUI {
    /**
     * @brief Class to handle video playback (MPEG1 only)
     *
     * @example:
     *
        #include "Video.hpp"
        #include "Window.hpp"

        int main(void)
        {
            raylib::Window window(1280, 720, "raylib Example MPEG video playing");
            Video video("assets/rick.mpeg");

            while (!WindowShouldClose()) {
                if (IsKeyPressed(KEY_SPACE))
                    video.setRunning(video.isPaused());
                if (IsKeyPressed(KEY_R))
                    video.Rewind();
                if (IsKeyPressed(KEY_L))
                    video.Loop(!video.isLooping());
                if (IsKeyPressed(KEY_RIGHT))
                    video.setSpeed(video.getSpeed() * 1.5);
                if (IsKeyPressed(KEY_LEFT))
                    video.setSpeed(video.getSpeed() * 0.75);
    gs
                video.Update();

                BeginDrawing();
                {
                    ClearBackground(RAYWHITE);
                    video.Draw();
                }
                EndDrawing();
            }
        }
     */
    class Video {
    private:
        plm_t *_plm;
        double _framerate;
        double _samplerate;
        raylib::Image _Imframe;
        raylib::Texture _texture;
        bool _loop = false;
        bool _ended = false;
        bool _pause = false;
        double _speed;
        double _base_time;

    public:
        // clang-format off
        class InvalidFile : public std::exception {
        private:
            const std::string _message;
        public:
            explicit InvalidFile(const std::string &message): _message(message) {}
            explicit InvalidFile(const char *const message): _message(message) {}
            virtual ~InvalidFile() noexcept { }
            const char *what() const noexcept override { return _message.c_str(); }
        };
        // clang-format on

        Video(const std::string &file_path, bool loop = false, double speed = 1);
        Video(const char *file_path, bool loop = false, double speed = 1);
        ~Video();

        void Resume(void) { _pause = false; }
        void Pause(void) { _pause = true; }
        void setRunning(bool running) { _pause = !running; }

        void Loop(bool loop);

        bool isLooping(void) const { return _loop; }

        bool isEnded(void) const { return _ended; }

        bool isPaused() const { return _pause; }

        void setSpeed(double speed) { _speed = speed; }
        double getSpeed() const { return _speed; }

        void Rewind(void);

        void Update();

        // Center the video on the screen
        void Draw(Color color = WHITE) const;

        void Draw(int x, int y, Color color = WHITE) const;
    };
}
