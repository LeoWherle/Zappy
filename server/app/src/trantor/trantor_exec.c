/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/pcmd_args.h"
#include "trantor/gcmd.h"
#include "trantor/pcmd.h"
#include "trantor/player.h"
#include "trantor/string_utils.h"
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

static void execute_pcmd(trantor_t *trantor, player_t *player)
{
    pcmd_executor_t *executor = &player->pcmd_exec;
    pcmd_args_t args = {0};

    args.player = player;
    args.map = &(trantor->map);
    args.broadcast_msg = executor->arg;
    args.item = executor->item;
    args.players = trantor->players;
    args.cnb = trantor->params.players;
    args.log = trantor->log;
    COMMAND_FUNCS[executor->command](&args);
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
