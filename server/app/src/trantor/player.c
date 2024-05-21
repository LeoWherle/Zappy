/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player sourcez file
*/

#include "trantor/player.h"

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
    pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    response_buffer = vec_new(sizeof(char *), NULL, NULL);
    busy = false;
}

void init_egg(player_t *player, team_t team, len_t x, len_t y)
{
    player->is_egg = true;
    player->team = team;
    player->x = x;
    player->y = y;
}

void hatch_egg(player_t *player)
{
    player->is_egg = false;
    player->direction = UP; // MAKE RANDOM
    player->elevation = 1;
    pcmd_buffer = vec_new(sizeof(char *), NULL, NULL);
    response_buffer = vec_new(sizeof(char *), NULL, NULL);
    busy = false;
}

void destroy_player(player_t *player)
{
    vec_delete(player->pcmd_buffer);
}
