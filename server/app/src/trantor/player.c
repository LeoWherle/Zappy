/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player sourcez file
*/

#include "trantor/player.h"

#include <stddef.h>

void init_player(player_t *player, team_t team, len_t x, len_t y)
{
    player->is_egg = false;
    player->team = team;
    player->x = x;
    player->y = y;
    player->direction = UP;
    for (int i = 0; i < 7; i++) {
        player->inventory.items[i] = 0;
    }
    player->elevation = 1;
    player->pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    player->response_buffer = vec_new(sizeof(char *), NULL, NULL);
    player->busy = false;
}

void init_egg(player_t *player, team_t team, len_t x, len_t y)
{
    player->is_egg = true;
    player->team = team;
    player->x = x;
    player->y = y;
}

// MAKE RANDOM DIRECTION
void hatch_egg(player_t *player)
{
    player->is_egg = false;
    player->direction = UP;
    player->elevation = 1;
    player->pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    player->response_buffer = vec_new(sizeof(char *), NULL, NULL);
    player->busy = false;
}

void destroy_player(void *player)
{
    vec_delete(((player_t *)player)->pcmd_buffer);
}
