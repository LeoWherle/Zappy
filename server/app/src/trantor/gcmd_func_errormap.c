/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands funcs source file
*/

#include "trantor/gcmd.h"
#include "trantor/string_utils.h"

void gui_error(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    talk(&trantor->log, "suc\n");
}

void gui_msz(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    talkf(&trantor->log, "msz %d %d\n",
        trantor->map.width, trantor->map.height);
}

void gui_bct(trantor_t *trantor, gcmd_args_t *args)
{
    tile_t *tile =
        &trantor->map.tiles[args->pos[1] * trantor->map.width + args->pos[0]];

    talkf(&trantor->log, "bct %d %d %d %d %d %d %d %d %d\n",
        args->pos[0], args->pos[1],
        tile->items[0], tile->items[1], tile->items[2], tile->items[3],
        tile->items[4], tile->items[5], tile->items[6]);
}

void gui_mct(trantor_t *trantor, gcmd_args_t *args)
{
    for (len_t y = 0; y < trantor->map.height; y++) {
        for (len_t x = 0; x < trantor->map.width; x++) {
            args->pos[0] = x;
            args->pos[1] = y;
            gui_bct(trantor, args);
        }
    }
}

void gui_tna(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    for (unsigned int i = 0; i < trantor->params.teams; i++)
        talkf(&trantor->log, "tna %s\n",
            (char *)vec_at(&trantor->params.team_names, i));
}
