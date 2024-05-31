/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "buffer.h"
#include "trantor.h"
#include "trantor/common.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
#include "trantor/map_fn.h"
#include "serrorh.h"
#include "vector.h"

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
        if (vec_push(&trantor->players, &p) != BUF_OK) {
            free(p);
            LOG_ERROR("Failed to add player to vector");
        }
    }
}

void init_trantor(trantor_t *trantor)
{
    init_map(trantor->params.width, trantor->params.height, &trantor->map);
    if (vec_init(&trantor->players,
        sizeof(player_t *), destroy_player, NULL) != BUF_OK)
        LOG_ERROR("Failed to init players vector");
    if (str_init(&trantor->log, "") != BUF_OK)
        LOG_ERROR("Failed to init log buffer");
    trantor->winning_team = -1;
    for (unsigned int i = 0; i < trantor->params.teams; i++) {
        add_initial_team_eggs(trantor, i);
    }
}

void feed_player_line(
    player_t *player, const char *line)
{
    if (player->npcmd > 10 || player->is_dead)
        return;
    talkf(&player->pcmd_buffer, "%s\n", line);
    player->npcmd++;
}

void gui_feed_trantor_line(trantor_t *trantor, const char *line)
{
    execute_gcmd(trantor, line);
}

void remove_player(trantor_t *trantor, player_t *player)
{
    player_t *other;

    for (unsigned int i = 0; i < trantor->players.nmemb; i++) {
        other = vec_at(&trantor->players, i);
        if (other->incantator == player)
            other->incantator = NULL;
    }
    talk(&player->response_buffer, "dead\n");
    player->is_dead = true;
    talkf(&trantor->log, "pdi %d\n", player->n);
}

void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_reset(&trantor->players);
    destroy_params(&trantor->params);
    str_reset(&trantor->log);
}
