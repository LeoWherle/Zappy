/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/common.h"
#include "trantor/map.h"
#include "trantor/string_utils.h"
#include "trantor/map_fn.h"
#include "serrorh.h"

#include <string.h>
#include <stdlib.h>

static void add_initial_team_eggs(
    trantor_t *trantor, team_t tm)
{
    player_t *p;
    coord_t c = {0};

    for (unsigned int i = 0; i < trantor->params.players; i++) {
        c[0] = rand() % trantor->params.width;
        c[1] = rand() % trantor->params.height;
        p = malloc(sizeof(player_t));
        if (p == NULL) {
            continue;
        }
        init_egg(p, tm, c);
        if (vec_push(trantor->players, p) != BUF_OK) {
            free(p);
            LOG_ERROR("Failed to add player to vector");
        }
    }
}

void init_trantor(trantor_t *trantor)
{
    init_map(trantor->params.width, trantor->params.height, &trantor->map);
    trantor->players = vec_new(sizeof(player_t), destroy_player, NULL);
    trantor->log = str_new();
    trantor->winning_team = -1;
    for (unsigned int i = 0; i < trantor->params.teams; i++) {
        add_initial_team_eggs(trantor, i);
    }
}

void feed_player_line(
    player_t *player, const char *line)
{
    if (player->npcmd > 10)
        return;
    talkf(player->pcmd_buffer, "%s\n", line);
    player->npcmd++;
}

void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
    execute_gcmd(trantor, line);
}

void remove_player(trantor_t *trantor, player_t *player)
{
    player_t *other;
    int idx = -1;

    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        other = vec_at(trantor->players, i);
        if (other == player)
            idx = i;
        if (other->incantator == player)
            other->incantator = NULL;
    }
    if (vec_remove(trantor->players, idx) != BUF_OK)
        LOG_ERROR("Failed to remove player from vector");
    talkf(trantor->log, "pdi %d\n", player->n);
}

void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->players);
    destroy_params(&trantor->params);
    str_delete(trantor->log);
}
