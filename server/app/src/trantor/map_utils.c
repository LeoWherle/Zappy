/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map source file
*/

#include "trantor/map.h"

#include <math.h>
#include <string.h>

const int DIRECTIONS[4][2] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

void player_move(player_t *player, map_t *map, direction_t direction)
{
    int new_x = ((int)player->x) + DIRECTIONS[direction][0];
    int new_y = ((int)player->y) + DIRECTIONS[direction][1];

    if (new_x < 0)
        new_x = ((int) map->width) - 1;
    if (new_y < 0)
        new_y = ((int) map->height) - 1;
    if (new_x >= ((int) map->width))
        new_x = 0;
    if (new_y >= ((int) map->height))
        new_y = 0;
    player->x = (len_t) new_x;
    player->y = (len_t) new_y;
}

tile_t *unbounded_tile_get(map_t *map, int x, int y)
{
    x = (x + (int) map->width) % (int) map->width;
    y = (y + (int) map->height) % (int) map->height;
    return GET_TILE(map, (len_t) x, (len_t) y);
}

static float get_distance(unbounded_coord_t a, unbounded_coord_t b)
{
    return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

static void fill_u_bs(
    map_t *map, unbounded_coord_t u_b, unbounded_coord_t *u_bs)
{
    unbounded_coord_t tmp[9] = {
        {u_b[0], u_b[1]},
        {u_b[0] - (int) map->width, u_b[1]},
        {u_b[0] + (int) map->width, u_b[1]},
        {u_b[0], u_b[1] - (int) map->height},
        {u_b[0], u_b[1] + (int) map->height},
        {u_b[0] - (int) map->width, u_b[1] - (int) map->height},
        {u_b[0] + (int) map->width, u_b[1] - (int) map->height},
        {u_b[0] - (int) map->width, u_b[1] + (int) map->height},
        {u_b[0] + (int) map->width, u_b[1] + (int) map->height}
    };

    memcpy(u_bs, tmp, sizeof(tmp));
}

void get_true_closest_coord(
    map_t *map, coord_t a, coord_t b, unbounded_coord_t *res)
{
    unbounded_coord_t u_a = {(int) a[0], (int) a[1]};
    unbounded_coord_t u_b = {(int) b[0], (int) b[1]};
    unbounded_coord_t u_bs[9] = {0};
    float min_dist = 999999999.0f;
    float dist;

    fill_u_bs(map, u_b, u_bs);
    for (unsigned int i = 0; i < 9; i++) {
        dist = get_distance(u_a, u_bs[i]);
        if (dist < min_dist) {
            min_dist = dist;
            (*res)[0] = u_bs[i][0];
            (*res)[1] = u_bs[i][1];
        }
    }
}
