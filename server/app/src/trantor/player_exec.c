/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "buffer.h"
#include "serrorh.h"
#include "sstrings.h"
#include "trantor.h"
#include "trantor/config.h"
#include "trantor/item.h"
#include "trantor/pcmd_args.h"
#include "trantor/pcmd.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
#include "trantor/tile.h"
#include "vector.h"


static int winning_team(vector_t *players, unsigned int teams)
{
    vector_t tcounts = {0};
    player_t *p;
    unsigned int i = 0;

    if (vec_init(&tcounts, sizeof(unsigned int), NULL, NULL) != BUF_OK
        || vec_reserve(&tcounts, teams) != BUF_OK)
        return -1;
    for (; i < players->nmemb; i++) {
        p = vec_at(players, i);
        if (p->team >= teams)
            continue;
        ((unsigned int *)tcounts.items)[p->team]++;
    }
    for (i = 0; i < tcounts.nmemb; i++)
        if (((unsigned int *) tcounts.items)[i] >= 6)
            return i;
    vec_reset(&tcounts);
    return -1;
}

static void handle_game_end(trantor_t *trantor)
{
    const char *wtname = NULL;

    if (trantor->winning_team == -1)
        return;
    wtname = vec_at(&trantor->params.team_names, trantor->winning_team);
    talkf(&trantor->log, "seg %s\n", wtname);
}

static void execute_pcmd(trantor_t *trantor, player_t *player)
{
    pcommand_t command = player->pcmd_exec.command;
    pcmd_args_t args = {0};

    args.spam_gui = trantor->params.spam_gui;
    args.player = player;
    args.map = &(trantor->map);
    args.broadcast_msg = player->pcmd_exec.arg;
    args.item = player->pcmd_exec.item;
    args.players = &trantor->players;
    args.cnb = count_idxteam_egg(trantor, player->team);
    args.log = &trantor->log;
    player->busy = false;
    get_pcmd_func(command)(&args);
    if (command != INCANTATION_PCMD)
        return;
    trantor->winning_team = winning_team(
            &trantor->players, trantor->params.teams);
    handle_game_end(trantor);
}

static void start_invocation(
    vector_t *players, player_t *invocator, string_t *log)
{
    player_t *p;

    talkf(log, "pic %d %d %d %d", invocator->coord[0], invocator->coord[1],
        invocator->elevation, invocator->n);
    for (unsigned int i = 0; i < players->nmemb; i++) {
        p = vec_at(players, i);
        if (!COORD_EQ(p->coord, invocator->coord)
            || p->elevation != invocator->elevation
            || p == invocator)
            continue;
        p->incantator = invocator;
        talkf(log, " %d", p->n);
    }
}

static void send_anim_signal(trantor_t *t, player_t *p)
{
    if (PCMD_NEEDS_OBJ(p->pcmd_exec.command)) {
        talkf(&t->log, get_pcmd_anim_ev_fmt(p->pcmd_exec.command),
            p->n, p->pcmd_exec.item);
    } else {
        talkf(&t->log, get_pcmd_anim_ev_fmt(p->pcmd_exec.command), p->n);
    }
}

static bool handle_invoc_task(trantor_t *t, player_t *p)
{
    if (!can_invocate(&t->players, p, &(t->map))) {
        SAY_KO(&p->response_buffer);
        return false;
    }
    start_invocation(&t->players, p, &t->log);
    return true;
}

static bool start_new_task(trantor_t *t, player_t *p)
{
    p->busy = false;
    if (p->npcmd == 0 || p->is_dead || p->is_egg)
        return false;
    init_pcmd_executor(p->pcmd_buffer.items, &p->pcmd_exec);
    if (p->pcmd_exec.command == NONE_PCMD) {
        SAY_KO(&p->response_buffer);
        return false;
    }
    if (PCMD_ANIMATED(p->pcmd_exec.command))
        send_anim_signal(t, p);
    p->npcmd--;
    LOG_TRACE("P %d starting %s\n", p->n, get_pcmd_name(p->pcmd_exec.command));
    if (p->pcmd_exec.command == INCANTATION_PCMD
        && !handle_invoc_task(t, p)) {
        SAY_KO(&p->response_buffer);
        return true;
    }
    p->busy = true;
    return true;
}

static bool death_from_hunger(trantor_t *trantor, player_t *player)
{
    if (HAS_ITEM(player->inventory, FOOD_ITEM)) {
        TAKE_ITEM(player->inventory, FOOD_ITEM);
        player->time_left += FOOD_LIFE_UNIT;
        return false;
    } else {
        remove_player(trantor, player);
        return true;
    }
}

void player_time_pass(
    trantor_t *trantor, float delta, unsigned int i)
{
    player_t *p = VEC_AT(&trantor->players, i);

    if (p->is_egg || p->is_dead)
        return;
    p->time_left -= delta;
    if (p->time_left <= 0 && death_from_hunger(trantor, p))
        return;
    if (p->incantator != NULL)
        return;
    p->pcmd_exec.exec_time_left -= delta;
    if (p->busy && p->pcmd_exec.exec_time_left <= 0) {
        execute_pcmd(trantor, p);
        p = VEC_AT(&trantor->players, i);
    }
    if ((!p->busy || p->pcmd_exec.exec_time_left <= 0)
        && start_new_task(trantor, p))
        pop_line(&p->pcmd_buffer);
}
