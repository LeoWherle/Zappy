/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** map source file
*/

#include "trantor/direction.h"
#include "trantor/map_fn.h"

const int DIRECTIONS[4][2] = {
    {0, -1},
    {1, 0},
    {0, 1},
    {-1, 0}
};

void add_direction(unbounded_coord_t *coord, direction_t direction)
{
    (*coord)[0] += DIRECTIONS[direction][0];
    (*coord)[1] += DIRECTIONS[direction][1];
}

void player_move(player_t *player, map_t *map, direction_t direction)
{
    int new_x = ((int)player->coord[0]) + DIRECTIONS[direction][0];
    int new_y = ((int)player->coord[1]) + DIRECTIONS[direction][1];

    if (new_x < 0)
        new_x = ((int) map->width) - 1;
    if (new_y < 0)
        new_y = ((int) map->height) - 1;
    if (new_x >= ((int) map->width))
        new_x = 0;
    if (new_y >= ((int) map->height))
        new_y = 0;
    player->coord[0] = (len_t) new_x;
    player->coord[1] = (len_t) new_y;
}

void bound_coord(map_t *map, unbounded_coord_t coord, coord_t *res)
{
    (*res)[0] = (len_t) ((coord[0] + (int) map->width) % (int) map->width);
    (*res)[1] = (len_t) ((coord[1] + (int) map->height) % (int) map->height);
}

tile_t *unbounded_tile_get(map_t *map, int x, int y)
{
    x = (x + (int) map->width) % (int) map->width;
    y = (y + (int) map->height) % (int) map->height;
    return GET_TILE(map, (len_t) x, (len_t) y);
}

void get_loc_tile_line(map_t *map, ray_t ray, len_t len, loc_tile_t *tiles)
{
    unbounded_coord_t pos = {ray.start[0], ray.start[1]};

    for (len_t i = 0; i < len; i++) {
        tiles[i].tile = unbounded_tile_get(map, pos[0], pos[1]);
        bound_coord(map, pos, &tiles[i].coord);
        tiles[i].nplayer = 0;
        pos[0] += DIRECTIONS[ray.direction][0];
        pos[1] += DIRECTIONS[ray.direction][1];
    }
}
