/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands funcs source file
*/

#include "trantor/gcmd.h"

void gui_error(trantor_t *trantor, gcmd_args_t *args)
{
    vec_push(&trantor->log, strdup("suc"));
}

void gui_msz(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    asprintf(&msg, "msz %d %d", trantor->map.width, trantor->map.height);
    vec_push(&trantor->log, msg);
}

void gui_bct(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    tile_t *tile =
        &trantor->map.tiles[args->pos[1] * trantor->map.width + args->pos[0]];

    asprintf(&msg, "bct %d %d %d %d %d %d %d %d %d",
        args->pos[0], args->pos[1],
        tile->items[0], tile->items[1], tile->items[2], tile->items[3],
        tile->items[4], tile->items[5], tile->items[6]);
    vec_push(&trantor->log, msg);
}

void gui_mct(trantor_t *trantor, gcmd_args_t *args)
{
    gcmd_args_t args;

    for (len_t y = 0; y < trantor->map.height; y++) {
        for (len_t x = 0; x < trantor->map.width; x++) {
            args.pos = {x, y};
            gui_bct(trantor, &args);
        }
    }
}

void gui_tna(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    for (unsigned int i = 0; i < trantor->params.teams; i++) {
        asprintf(&msg, "tna %s", trantor->params.team_names[i]);
        vec_push(&trantor->log, msg);
    }
}

void gui_ppo(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    player_t *player = vec_get(&trantor->players, args->n);

    asprintf(&msg, "ppo %d %d %d %d", args->n,
        player->x, player->y, player->direction + 1);
    vec_push(&trantor->log, msg);
}

void gui_plv(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    player_t *player = vec_get(&trantor->players, args->n);

    asprintf(&msg, "plv %d %d", args->n, player->elevation);
    vec_push(&trantor->log, msg);
}

void gui_pin(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    player_t *player = vec_get(&trantor->players, args->n);

    asprintf(&msg, "pin %d %d %d %d %d %d %d %d %d %d",
        args->n, player->x, player->y, player->inventory.items[0],
        player->inventory.items[1], player->inventory.items[2],
        player->inventory.items[3], player->inventory.items[4],
        player->inventory.items[5], player->inventory.items[6]);
    vec_push(&trantor->log, msg);
}

void gui_sgt(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    asprintf(&msg, "sgt %f", 0.0f); // replace by actual time or f ?
    vec_push(&trantor->log, msg);
}

void gui_sst(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;

    asprintf(&msg, "sst %f", 0.0f); // same
    vec_push(&trantor->log, msg);
}
