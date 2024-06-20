/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands funcs source file
*/

#include "trantor.h"
#include "trantor/gcmd.h"

void gui_psd(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    trantor_pause(trantor);
    if (trantor->paused)
        trantor_time_pass(trantor, 0.0f, true);
}

void gui_rst(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    reset_trantor(trantor);
}

void gui_nxt(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    float fake_delta = trantor_min_time(trantor);

    trantor_time_pass(trantor, fake_delta, false);
}
