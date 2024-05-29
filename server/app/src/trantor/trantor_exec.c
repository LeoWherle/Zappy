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
#include "trantor/item.h"
#include "trantor/pcmd_args.h"
#include "trantor/gcmd.h"
#include "trantor/pcmd.h"
#include "trantor/player.h"
#include "trantor/map_fn.h"
#include "trantor/string_utils.h"
#include "trantor/tile.h"
#include "vector.h"

pcmd_func_t COMMAND_FUNCS[PCMD_COUNT] = {
    player_error, player_forward, player_right, player_left, player_look,
    player_inventory, player_broadcast, player_co_num, player_fork,
    player_eject, player_take, player_set, player_incantation
};

gcmd_func_t GCOMMAND_FUNCS[10] = {
    gui_error, gui_msz, gui_bct, gui_mct, gui_tna,
    gui_ppo, gui_plv, gui_pin, gui_sgt, gui_sst
};

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
    vec_delete(&tcounts);
    return -1;
}

static void handle_game_end(trantor_t *trantor)
{
    const char *wtname = NULL;

    if (trantor->winning_team == -1)
        return;
    wtname = vec_at(trantor->params.team_names, trantor->winning_team);
    talkf(trantor->log, "seg %s\n", wtname);
}

static void execute_pcmd(trantor_t *trantor, player_t *player)
{
    pcmd_executor_t *executor = &player->pcmd_exec;
    pcmd_args_t args = {0};

    args.player = player;
    args.map = &(trantor->map);
    args.broadcast_msg = executor->arg;
    args.item = executor->item;
    args.players = trantor->players;
    args.cnb = count_idxteam_egg(trantor, player->team);
    args.log = trantor->log;
    COMMAND_FUNCS[executor->command](&args);
    player->busy = false;
    if (executor->command != INCANTATION_PCMD)
        return;
    trantor->winning_team = winning_team(
            trantor->players, trantor->params.teams);
    handle_game_end(trantor);
}

void execute_gcmd(trantor_t *trantor, const char *gcmd)
{
    gcmd_args_t args = {0};
    gcommand_t command = parse_gcmd(gcmd, &args);

    if (command == NONE_GCMD) {
        gui_error(trantor, &args);
        return;
    }
    GCOMMAND_FUNCS[command](trantor, &args);
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

static void start_new_task(trantor_t *trantor, player_t *player)
{
    player->busy = false;
    if (player->npcmd == 0)
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
        start_invocation(trantor->players, player, trantor->log);
    }
    player->busy = true;
    pop_line(player->pcmd_buffer);
    player->npcmd--;
}

static void try_refill_map(trantor_t *trantor, double delta)
{
    trantor->map.since_refill += delta;
    if (trantor->map.since_refill >= 20) {
        add_ressources(&(trantor->map));
        trantor->map.since_refill = 0.0;
    }
}

static bool death_from_hunger(trantor_t *trantor, player_t *player)
{
    if (HAS_ITEM(player->inventory, FOOD_ITEM)) {
        TAKE_ITEM(player->inventory, FOOD_ITEM);
        player->time_left += 126.0 / trantor->params.f;
        return false;
    } else {
        remove_player(trantor, player);
        return true;
    }
}

void player_time_pass(
    trantor_t *trantor, double delta, player_t *player, unsigned int *i)
{
    if (player->is_egg)
        return;
    player->time_left -= delta;
    if (player->time_left <= 0 && death_from_hunger(trantor, player)) {
        (*i)--;
        return;
    }
    if (player->incantator != NULL)
        return;
    player->pcmd_exec.exec_time_left -= delta;
    if (player->busy && player->pcmd_exec.exec_time_left <= 0)
        execute_pcmd(trantor, player);
    if (!player->busy || player->pcmd_exec.exec_time_left <= 0)
        start_new_task(trantor, player);
}

bool trantor_time_pass(trantor_t *trantor, double delta)
{
    try_refill_map(trantor, delta);
    for (unsigned int i = 0; i < trantor->players->nmemb; i++) {
        player_time_pass(trantor, delta, vec_at(trantor->players, i), &i);
    }
    return (trantor->winning_team == -1);
}
