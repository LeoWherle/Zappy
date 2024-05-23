/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player sourcez file
*/

#include "trantor/player.h"

#include <stdlib.h>


void init_egg(player_t *player, team_t team, len_t x, len_t y)
{
    static unsigned int last_n_given = 0;

    player->is_egg = true;
    player->team = team;
    player->x = x;
    player->y = y;
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
    player->pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    player->response_buffer = vec_new(sizeof(char *), NULL, NULL);
    player->busy = false;
}

void destroy_player(void *player)
{
    vec_delete(((player_t *)player)->pcmd_buffer);
    vec_delete(((player_t *)player)->response_buffer);
}
