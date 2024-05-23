/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "buffer.h"
#include "trantor/map.h"
#include "trantor/pcmd_args.h"
#include "trantor/tile.h"
#include "trantor/string_utils.h"

#include <stdlib.h>
#include <stdio.h>

const char *ITEM_NAMES[7] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

static tile_t **internal_player_look(pcmd_args_t *args, size_t *lenbuf)
{
    direction_t ray_dir = (args->player->direction + 1) % 4;
    unbounded_coord_t start =
        {(int) args->player->x, (int) args->player->y};
    tile_t **tiles;
    size_t len = 1;

    for (unsigned int i = 0; i < args->player->elevation; i++)
        len += i * 2 + 1;
    tiles = malloc(sizeof(tile_t *) * len);
    *lenbuf = len;
    tiles[0] = unbounded_tile_get(args->map, start[0], start[1]);
    len = 1;
    for (unsigned int i = 0; i < args->player->elevation; i++) {
        add_direction(&start, args->player->direction);
        add_direction(&start, (ray_dir + 2) % 4);
        get_tile_line(args->map,
            (ray_t){{start[0], start[1]}, ray_dir}, i * 2 + 1, tiles + len);
        len += i * 2 + 1;
    }
    return tiles;
}

static size_t get_tile_req_size(tile_t *tile)
{
    size_t len = 0;

    for (unsigned int i = 0; i < 7; i++) {
        len += ((strlen(ITEM_NAMES[i]) + 1) * tile->items[i]);
    }
    return len - 1;
}

static void sprintf_tile(char *msg, tile_t *tile, size_t *len)
{
    for (unsigned int i = 0; i < 7; i++) {
        for (unsigned int j = 0; j < tile->items[i]; j++) {
            *len += (j != tile->items[i] - 1) ?
                sprintf(msg + *len, "%s ", ITEM_NAMES[i])
                : sprintf(msg + *len, "%s", ITEM_NAMES[i]);
        }
    }
}

void player_look(pcmd_args_t *args)
{
    char *msg = NULL;
    size_t tnb = 0;
    tile_t **tiles = internal_player_look(args, &tnb);
    size_t len = 3 + ((tnb - 1) * 2);

    for (size_t i = 0; i < tnb; i++)
        len += get_tile_req_size(tiles[i]);
    if (vec_reserve(str_to_vec(args->player->response_buffer), len) != BUF_OK)
        return;
    msg = STRING_END(args->player->response_buffer);
    len = sprintf(msg, "[");
    for (size_t i = 0; i < tnb; i++) {
        sprintf_tile(msg + len, tiles[i], &len);
        if (i != tnb - 1)
            len += sprintf(msg + len, ", ");
    }
    len += sprintf(msg + len, "]\n");
    talk(args->player->response_buffer, msg);
}

void player_inventory(pcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 2 + 6 + 1;

    for (unsigned int i = 0; i < 7; i++)
        len += snprintf(NULL, 0, "%s %d", ITEM_NAMES[i],
            args->player->inventory.items[i]);
    if (vec_reserve(str_to_vec(args->player->response_buffer), len) != BUF_OK)
        return;
    msg = STRING_END(args->player->response_buffer);
    len = sprintf(msg, "[");
    for (unsigned int i = 0; i < 7; i++) {
        len += sprintf(msg + len, "%s %d", ITEM_NAMES[i],
            args->player->inventory.items[i]);
        if (i != 6)
            len += sprintf(msg + len, ", ");
    }
    len += sprintf(msg + len, "]\n");
    talk(args->player->response_buffer, msg);
}

void player_co_num(pcmd_args_t *args)
{
    talkf(args->player->response_buffer, "%d\n", args->cnb);
}

void player_take(pcmd_args_t *args)
{
    item_t i;
    tile_t *t;

    t = GET_TILE(args->map, args->player->x, args->player->y);
    if (!HAS_ITEM(*t, args->item)) {
        SAY_KO(args->player->response_buffer);
        return;
    }
    i = TAKE_ITEM(*t, args->item);
    ADD_ITEM(args->player->inventory, i);
    SAY_OK(args->player->response_buffer);
}
