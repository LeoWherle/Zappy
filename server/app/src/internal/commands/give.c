/*
** EPITECH PROJECT, 2024
** B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
** File description:
** give
*/

#include "commands/give.h"
#include "buffer.h"
#include "serrorh.h"
#include "string/macros.h"
#include "trantor/common.h"
#include "trantor/item.h"
#include "trantor/player.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>

give_cmd_t targets[] = {
    {"all", 'a', give_all},
    {"random", 'r', give_random},
    {"player", 'p', give_player},
    {"team", 't', give_team},
};

static void give_player_ressource(player_t *player, give_data_t *item)
{
    player->inventory.items[item->type] += item->amount;
}

static bool fetch_give_data(give_data_t *data, vector_t *args, size_t arg_pos)
{
    char *item = NULL;

    if (args->nmemb != 2) {
        LOG_ERROR("Expected: give @target <resource> <quantity>");
        return false;
    }
    item = VEC_STR(args, arg_pos + 0);
    data->type = get_item_type(item);
    if (data->type == NONE_ITEM) {
        LOG_ERROR("Invalid resource: %.*s", (int) strlen(item), item);
        return false;
    }
    data->amount = strtoul(*(char **) VEC_STR(args, arg_pos + 1), NULL, 10);
    return true;
}

void give_all(server_t *serv, vector_t *args)
{
    give_data_t item = {0};

    if (args->nmemb != 2)
        return (void) LOG_ERROR("Expected: give @a <resource> quantity");
    if (fetch_give_data(&item, args, 0))
        return;
    for (size_t i = 0; i < serv->trantor.players.nmemb; i++) {
        give_player_ressource(VEC_AT(&serv->trantor.players, i), &item);
    }
    LOG_INFO("Gave %d %*.s to %lu players", item.amount,
        (int) strlen(VEC_STR(args, 0)), VEC_STR(args, 0),
        serv->trantor.players.nmemb);
}

void give_random(server_t *serv, vector_t *args)
{
    give_data_t item = {0};
    int random = 0;

    if (args->nmemb != 2)
        return (void) LOG_ERROR("Expected: give @r <resource> quantity");
    if (fetch_give_data(&item, args, 0))
        return;
    if (serv->trantor.players.nmemb != 0) {
        return (void) LOG_ERROR("No players to give resources to");
    }
    random = rand() % serv->trantor.players.nmemb;
    give_player_ressource(VEC_AT(&serv->trantor.players, random), &item);
}

static bool player_find_by_id(const void *player, void *id)
{
    return ((player_t *) player)->n == *(size_t *) id;
}

// give @p <id> <resource> <quantity>
void give_player(server_t *serv, vector_t *args)
{
    size_t id = 0;
    give_data_t item = {0};
    player_t *playr = NULL;

    if (args->nmemb != 3)
        return (void) LOG_ERROR("Expected: give @p <id> <resource> quantity");
    id = strtoul(*(const char **) VEC_STR(args, 0), NULL, 10);
    if (fetch_give_data(&item, args, 1))
        return;
    playr = vec_find_arg(&serv->trantor.players, player_find_by_id, &id);
    if (playr == NULL)
        return (void) LOG_ERROR("Player not found: %lu", id);
    give_player_ressource(playr, &item);
}

void give_team(server_t *serv, vector_t *args)
{
    int team_id = 0;
    give_data_t item = {0};
    player_t *playr = NULL;

    if (args->nmemb != 3)
        return (void) LOG_ERROR(
            "Expected: give @t <team_name> <resource> quantity");
    team_id = get_team_index(&serv->trantor.params, VEC_STR(args, 0));
    if (team_id == -1)
        return (void) LOG_ERROR("Invalid team: %s", VEC_STR(args, 0));
    if (fetch_give_data(&item, args, 1))
        return;
    for (size_t i = 0; i < serv->trantor.players.nmemb; i++) {
        playr = VEC_AT(&serv->trantor.players, i);
        if (playr->team == (team_t) team_id)
            give_player_ressource(VEC_AT(&serv->trantor.players, i), &item);
    }
}

// give @target$ <resource> <quantity>
void command_give(
    server_t *server, UNUSED serv_context_t *context, vector_t *args)
{
    const char *target = NULL;
    bool found = false;
    UNUSED buf_error_t err = BUF_OK;

    if (args->nmemb < 2)
        return (void) LOG_ERROR("Expected: give all|random|player|team ...");
    target = *(const char **) vec_at(args, 1);
    for (size_t i = 0; i < sizeof(targets) / sizeof(*targets); i++) {
        found = !strcasecmp(target, targets[i].target)
            || (strlen(target) == 2 && target[0] == '@'
                && target[1] == targets[i].target_short);
        if (found) {
            err = vec_erase(args, 0, 2);
            return targets[i].callback(server, args);
        }
    }
    return (void) LOG_ERROR("Invalid target: %s", target);
}
