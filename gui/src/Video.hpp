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

#include "Image.hpp"
#include "Texture.hpp"

#define PL_MPEG_IMPLEMENTATION
#include "pl_mpeg.h"

/**
 * @brief Class to handle video playback (MPEG1 only)
 *
 * @example:
 * 
    #include "Window.hpp"
    #include "Video.hpp"

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
    double _base_time = GetTime();

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

    Video(const std::string &file_path, bool loop = false)
    {
        _plm = plm_create_with_filename(file_path.c_str());
        if (_plm == nullptr) {
            throw InvalidFile("Failed to open video file");
        }
        _framerate = plm_get_framerate(_plm);
        _samplerate = plm_get_samplerate(_plm);
        _Imframe.width = plm_get_width(_plm);
        _Imframe.height = plm_get_height(_plm);
        _Imframe.mipmaps = 1;
        _Imframe.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
        _Imframe.data = RL_MALLOC(_Imframe.width * _Imframe.height * 3);
        plm_set_loop(_plm, loop);

        _texture.Load(_Imframe);
    }

    Video(const char *file_path, bool loop = false)
    {
        _plm = plm_create_with_filename(file_path);
        if (_plm == nullptr) {
            throw InvalidFile("Failed to open video file");
        }
        _framerate = plm_get_framerate(_plm);
        _samplerate = plm_get_samplerate(_plm);
        _Imframe.width = plm_get_width(_plm);
        _Imframe.height = plm_get_height(_plm);
        _Imframe.mipmaps = 1;
        _Imframe.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
        _Imframe.data = RL_MALLOC(_Imframe.width * _Imframe.height * 3);
        plm_set_loop(_plm, loop);

        _texture.Load(_Imframe);
    }

    void Resume(void) { _pause = false; }
    void Pause(void) { _pause = true; }
    void setRunning(bool running) { _pause = !running; }

    void Loop(bool loop)
    {
        _ended = false;
        plm_set_loop(_plm, loop);
    }

    bool isLooping(void) const { return _loop; }

    bool isEnded(void) const { return _ended; }

    bool isPaused() const { return _pause; }

    void Rewind(void)
    {
        _ended = false;
        bool old = plm_get_loop(_plm);
        plm_set_loop(_plm, true);
        plm_rewind(_plm);
        plm_set_loop(_plm, old);
    }

    void Update()
    {
        plm_frame_t *frame = nullptr;

        if (_pause || _ended)
            return;

        double time = (GetTime() - _base_time);

        if (time >= 1.0 / _framerate) {
            _base_time = GetTime();

            // Decode video frame
            frame = plm_decode_video(_plm);
            if (frame) {
                plm_frame_to_rgb(frame, (uint8_t *) _Imframe.data, _Imframe.width * 3);
                _texture.Update(_Imframe.data);
            } else {
                memset(_Imframe.data, 0, _Imframe.width * _Imframe.height * 3);
                _texture.Update(_Imframe.data);
            }
            if (plm_has_ended(_plm)) {
                if (_loop) {
                    plm_rewind(_plm);
                }
            }
        }
    }

    // Center the video on the screen
    void Draw(Color color = WHITE) const
    {
        _texture.Draw(
            GetScreenWidth() / 2 - _texture.width / 2, GetScreenHeight() / 2 - _texture.height / 2, color
        );
    }

    void Draw(int x, int y, Color color = WHITE) const { _texture.Draw(x, y, color); }

    ~Video()
    {
        if (_plm != nullptr) {
            plm_destroy(_plm);
        }
    }
};
