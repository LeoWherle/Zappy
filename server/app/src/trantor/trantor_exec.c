/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/config.h"
#include "trantor/player.h"
#include "trantor/map_fn.h"
#include "vector.h"
#include "trantor/string_utils.h"

static void try_refill_map(trantor_t *trantor, float delta)
{
    trantor->map.since_refill += delta;
    if (trantor->map.since_refill
        >= MAP_REFILLS_INTERVAL) {
        add_ressources(&(trantor->map));
        trantor->map.since_refill -= MAP_REFILLS_INTERVAL;
    }
}

bool trantor_time_pass(trantor_t *trantor, float delta, bool real_time)
{
    float _delta = real_time ? delta * trantor->params.f : delta;

    if (trantor->paused || _delta <= 0.0f)
        return (trantor->winning_team == -1);
    try_refill_map(trantor, _delta);
    for (unsigned int i = 0; i < trantor->players.nmemb; i++) {
        player_time_pass(trantor, _delta, i);
    }
    if (trantor->params.spam_gui) {
        trantor->since_spam += _delta;
        if (trantor->since_spam >= SPAM_INTERVAL) {
            execute_gcmd(trantor, "mct");
            trantor->since_spam -= SPAM_INTERVAL;
        }
    }
    return (trantor->winning_team == -1);
}

float trantor_min_time(trantor_t *trantor)
{
    player_t *p;
    float min_time = 999999999.0;

    for (unsigned int i = 0; i < trantor->players.nmemb; i++) {
        p = VEC_AT(&trantor->players, i);
        if (p->is_egg || p->is_dead)
            continue;
        if (p->time_left < min_time)
            min_time = p->time_left;
        if (p->busy && p->pcmd_exec.exec_time_left < min_time)
            min_time = p->pcmd_exec.exec_time_left;
    }
    if (MAP_REFILLS_INTERVAL - trantor->map.since_refill < min_time)
        min_time = MAP_REFILLS_INTERVAL - trantor->map.since_refill;
    return min_time;
}

void trantor_pause(trantor_t *trantor)
{
    trantor->paused = !trantor->paused;
}

void remove_player(trantor_t *trantor, player_t *player)
{
    player_t *other;

    for (unsigned int i = 0; i < trantor->players.nmemb; i++) {
        other = VEC_AT(&trantor->players, i);
        if (other->incantator == player)
            other->incantator = NULL;
    }
    talk(&player->response_buffer, "dead\n");
    player->is_dead = true;
    talkf(&trantor->log, "pdi %d\n", player->n);
}
