/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player sourcez file
*/

#include "trantor/player.h"
#include "trantor/map.h"

#include <stdlib.h>


void init_egg(player_t *player, team_t team, coord_t c)
{
    static unsigned int last_n_given = 0;

    player->is_egg = true;
    player->team = team;
    player->coord[0] = c[0];
    player->coord[1] = c[1];
    player->incantator = NULL;
    player->n = last_n_given;
    last_n_given++;
}

void hatch_egg(player_t *player)
{
    player->is_egg = false;
    player->direction = rand() % 4;
    for (int i = 0; i < 7; i++) {
        player->inventory.items[i] = 0;
    }
    player->elevation = 1;
    player->pcmd_buffer = str_new();
    player->response_buffer = str_new();
    player->busy = false;
}

void destroy_player(void *player)
{
    str_delete(((player_t *)player)->pcmd_buffer);
    str_delete(((player_t *)player)->response_buffer);
}
