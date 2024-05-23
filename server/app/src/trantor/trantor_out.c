/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/map_fn.h"
#include "trantor/pcmd.h"
#include "trantor/pcmd_args.h"
#include "trantor/player.h"
#include "trantor/trantor_internal.h"
#include "trantor/string_utils.h"
#include "vector.h"

#include <stdlib.h>
#include <time.h>


void free_trantor(trantor_t *trantor)
{
    free_map(&trantor->map);
    vec_delete(trantor->players);
    destroy_params(&trantor->params);
}

player_t *hatch_team_egg(trantor_t *trantor, const char *team_name)
{
    player_t *temp;
    team_t team;
    int idx = get_team_index(&trantor->params, team_name);

    if (idx == -1)
        return NULL;
    team = (team_t) idx;
    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        temp = vec_at(trantor->players, i);
        if (!temp->is_egg || temp->team != team)
            continue;
        hatch_egg(temp);
        talkf(trantor->log, "pnw %d %d %d %d %d %s\n",
            temp->n, temp->coord[0], temp->coord[1], temp->direction,
            temp->elevation, team_name);
        return temp;
    }
    return NULL;
}

static void assign_invocator(vector_t *players, player_t *invocator)
{
    player_t *p;

    for (unsigned int i = 0; i < players->nmemb; i++) {
        p = vec_at(players, i);
        if (COORD_EQ(p->coord, invocator->coord)
            && p->elevation == invocator->elevation)
            p->incantator = invocator;
    }
}

static void start_new_task(trantor_t *trantor, player_t *player)
{
    player->busy = false;
    if (player->pcmd_buffer->nmemb == 0)
        return;
    init_pcmd_executor(player->pcmd_buffer->items,
        trantor->params.f, &player->pcmd_exec);
    if (player->pcmd_exec.command == NONE_PCMD) {
        SAY_KO(player->response_buffer);
        return;
    }
    if (player->pcmd_exec.command == INCANTATION_PCMD) {
        if (!can_invocate(trantor->players, player, &(trantor->map))) {
            SAY_KO(player->response_buffer);
            return;
        }
        assign_invocator(trantor->players, player);
    }
    player->busy = true;
    pop_line(player->pcmd_buffer);
}

void trantor_time_pass(trantor_t *trantor, double delta)
{
    player_t *player;

    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        player = vec_at(trantor->players, i);
        if (player->is_egg || player->incantator != NULL)
            continue;
        player->pcmd_exec.exec_time_left -= delta;
        if (player->busy && player->pcmd_exec.exec_time_left <= 0)
            execute_pcmd(trantor, player);
        if (!player->busy || player->pcmd_exec.exec_time_left <= 0) {
            start_new_task(trantor, player);
        }
    }
}

string_t *get_player_buffer(player_t *player)
{
    return player->response_buffer;
}

string_t *get_gui_buffer(trantor_t *trantor)
{
    return trantor->log;
}
