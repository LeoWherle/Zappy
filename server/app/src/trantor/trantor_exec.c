/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor source file
*/

#include "trantor.h"
#include "trantor/pcmd_args.h"
#include "trantor/gcmd.h"


pcmd_func_t COMMAND_FUNCS[PCMD_COUNT] = {
    player_error, player_forward, player_right, player_left, player_look,
    player_inventory, player_broadcast, player_co_num, player_fork,
    player_eject, player_take, player_set, player_incantation
};

gcmd_func_t GCOMMAND_FUNCS[10] = {
    gui_error, gui_msz, gui_bct, gui_mct, gui_tna,
    gui_ppo, gui_plv, gui_pin, gui_sgt, gui_sst
};

void execute_pcmd(trantor_t *trantor, player_t *player)
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
