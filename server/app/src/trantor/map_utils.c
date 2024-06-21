/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map source file
*/

#include "trantor/direction.h"
#include "trantor/map_fn.h"

#include <math.h>
#include <string.h>


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

static void get_true_closest_coord(
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

static unsigned int get_world_receiving_square(
    map_t *map, coord_t emiter, coord_t receiver)
{
    unbounded_coord_t u_emiter = {0};
    float slope = 0;

    if (emiter[0] == receiver[0] && emiter[1] == receiver[1])
        return 0;
    get_true_closest_coord(map, receiver, emiter, &u_emiter);
    if (u_emiter[0] == (int) receiver[0])
        return u_emiter[1] > (int) receiver[1] ? 1 : 5;
    slope = (float) (u_emiter[1] - (int) receiver[1]) /
        (float) (u_emiter[0] - (int) receiver[0]);
    if (slope < -3 || slope > 3)
        return u_emiter[1] > (int) receiver[1] ? 1 : 5;
    if (slope < -0.33)
        return u_emiter[0] > (int) receiver[0] ? 6 : 2;
    if (slope < 0.33)
        return u_emiter[0] > (int) receiver[0] ? 7 : 3;
    return u_emiter[1] > (int) receiver[1] ? 8 : 4;
}

unsigned int get_receiving_square(
    map_t *map, direction_t rdir, coord_t emiter, coord_t receiver)
{
    unsigned int world_square =
        get_world_receiving_square(map, emiter, receiver);

    if (world_square == 0)
        return 0;
    return (((world_square - 1) + rdir * 2) % 8) + 1;
}
