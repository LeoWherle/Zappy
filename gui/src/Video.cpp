/*
** EPITECH PROJECT, 2024
** gui [WSL: Ubuntu]
** File description:
** Video
*/

#include "Video.hpp"

Video::Video(const std::string &file_path, bool loop, double speed):
    _loop(loop),
    _base_time(GetTime()),
    _speed(speed)
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

Video::Video(const char *file_path, bool loop, double speed):
    _loop(loop),
    _base_time(GetTime()),
    _speed(speed)
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

Video::~Video()
{
    if (_plm != nullptr) {
        plm_destroy(_plm);
    }
}

void Video::Loop(bool loop)
{
    _ended = false;
    plm_set_loop(_plm, loop);
}

void Video::Rewind(void)
{
    _ended = false;
    bool old = plm_get_loop(_plm);
    plm_set_loop(_plm, true);
    plm_rewind(_plm);
    plm_set_loop(_plm, old);
}

void Video::Update()
{
    plm_frame_t *frame = nullptr;

    if (_pause || _ended)
        return;

    double time = (GetTime() - _base_time);

    if (time >= 1.0 / (_framerate * _speed)) {
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
void Video::Draw(Color color) const
{
    _texture.Draw(
        GetScreenWidth() / 2 - _texture.width / 2, GetScreenHeight() / 2 - _texture.height / 2, color
    );
}

void Video::Draw(int x, int y, Color color) const { _texture.Draw(x, y, color); }
