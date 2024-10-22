/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands funcs source file
*/

#include "trantor.h"
#include "trantor/gcmd.h"
#include "trantor/string_utils.h"

void gui_ppo(trantor_t *trantor, gcmd_args_t *args)
{
    player_t *player = vec_at(&trantor->players, args->n - 1);

    if (player == NULL) {
        talkf(&trantor->log, "suc\n");
        return;
    }
    talkf(&trantor->log, "ppo %d %d %d %d\n", args->n,
        player->coord[0], player->coord[1], player->direction + 1);
}

void gui_plv(trantor_t *trantor, gcmd_args_t *args)
{
    player_t *player = vec_at(&trantor->players, args->n - 1);

    if (player == NULL) {
        talkf(&trantor->log, "suc\n");
        return;
    }
    talkf(&trantor->log, "plv %d %d\n", args->n, player->elevation);
}

void gui_pin(trantor_t *trantor, gcmd_args_t *args)
{
    player_t *player = vec_at(&trantor->players, args->n - 1);

    if (player == NULL) {
        talkf(&trantor->log, "suc\n");
        return;
    }
    talkf(&trantor->log, "pin %d %d %d %d %d %d %d %d %d %d\n", args->n,
        player->coord[0], player->coord[1], player->inventory.items[0],
        player->inventory.items[1], player->inventory.items[2],
        player->inventory.items[3], player->inventory.items[4],
        player->inventory.items[5], player->inventory.items[6]);
}

void gui_sgt(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    talkf(&trantor->log, "sgt %d\n", (int) trantor->params.f);
}

void gui_sst(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    trantor->params.f = args->t;
    talkf(&trantor->log, "sst %d\n", (int) trantor->params.f);
}
