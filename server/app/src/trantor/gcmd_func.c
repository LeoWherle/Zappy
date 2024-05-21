/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands funcs source file
*/

#include "serrorh.h"
#include "trantor/gcmd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gui_error(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    if (vec_push(trantor->log, strdup("suc")) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}

void gui_msz(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;

    len = snprintf(NULL, 0, "msz %d %d", trantor->map.width, trantor->map.height);
    msg = malloc(len + 1);
    sprintf(msg, "msz %d %d", trantor->map.width, trantor->map.height);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}

void gui_bct(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;
    tile_t *tile =
        &trantor->map.tiles[args->pos[1] * trantor->map.width + args->pos[0]];

    len = snprintf(NULL, 0, "bct %d %d %d %d %d %d %d %d %d",
        args->pos[0], args->pos[1],
        tile->items[0], tile->items[1], tile->items[2], tile->items[3],
        tile->items[4], tile->items[5], tile->items[6]);
    msg = malloc(len + 1);
    sprintf(msg, "bct %d %d %d %d %d %d %d %d %d",
        args->pos[0], args->pos[1],
        tile->items[0], tile->items[1], tile->items[2], tile->items[3],
        tile->items[4], tile->items[5], tile->items[6]);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
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
    char *msg = NULL;
    size_t len = 0;

    for (unsigned int i = 0; i < trantor->params.teams; i++) {
        len = snprintf(NULL, 0, "tna %s", trantor->params.team_names[i]);
        msg = malloc(len + 1);
        sprintf(msg, "tna %s", trantor->params.team_names[i]);
        if (vec_push(trantor->log, msg) != BUF_OK)
            LOG_ERROR("Error while pushing to log");
    }
}

void gui_ppo(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;
    player_t *player = vec_at(trantor->players, args->n);

    len = snprintf(NULL, 0, "ppo %d %d %d %d", args->n,
        player->x, player->y, player->direction + 1);
    msg = malloc(len + 1);
    sprintf(msg, "ppo %d %d %d %d", args->n,
        player->x, player->y, player->direction + 1);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}

void gui_plv(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;
    player_t *player = vec_at(trantor->players, args->n);

    len = snprintf(NULL, 0, "plv %d %d", args->n, player->elevation);
    msg = malloc(len + 1);
    sprintf(msg, "plv %d %d", args->n, player->elevation);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}

void gui_pin(trantor_t *trantor, gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;
    player_t *player = vec_at(trantor->players, args->n);

    len = snprintf(NULL, 0, "pin %d %d %d %d %d %d %d %d %d %d",
        args->n, player->x, player->y, player->inventory.items[0],
        player->inventory.items[1], player->inventory.items[2],
        player->inventory.items[3], player->inventory.items[4],
        player->inventory.items[5], player->inventory.items[6]);
    msg = malloc(len + 1);
    sprintf(msg, "pin %d %d %d %d %d %d %d %d %d %d",
        args->n, player->x, player->y, player->inventory.items[0],
        player->inventory.items[1], player->inventory.items[2],
        player->inventory.items[3], player->inventory.items[4],
        player->inventory.items[5], player->inventory.items[6]);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}

void gui_sgt(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;

    len = snprintf(NULL, 0, "sgt %f", 0.0f); // replace by actual time or f ?
    msg = malloc(len + 1);
    sprintf(msg, "sgt %f", 0.0f);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}

void gui_sst(trantor_t *trantor, __attribute__((unused)) gcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 0;

    len = snprintf(NULL, 0, "sst %f", 0.0f); // same
    msg = malloc(len + 1);
    sprintf(msg, "sst %f", 0.0f);
    if (vec_push(trantor->log, msg) != BUF_OK)
        LOG_ERROR("Error while pushing to log");
}
