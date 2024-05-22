/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor header
*/

#pragma once

#include "trantor/player.h"
#include "trantor/map.h"
#include "trantor/params.h"

/**
 * @brief The trantor structure. This is the main structure of the server app.
 * It contains the map, the players, the log buffer and the last time the
 * server was updated.
 *
 * @param params the parameters of Trantor, see trantor/params.h
 * @param map the map of the server
 * @param players a vector of player_t *
 * @param log a vector of char * containing the log of the server, destined to
 * the GUI
 * @param last_time the last time the server was updated
 */
typedef struct trantor_s {
    trantor_params_t params;
    map_t map;
    vector_t *players;
    vector_t *log;
    double last_time;
} trantor_t;

void init_trantor(trantor_t *trantor, trantor_params_t *params);
void free_trantor(trantor_t *trantor);

/**
 * @brief Find an available unhatched egg from a team. Will return NULL if no
 * egg is found. This will hatch the egg and init necessary player fields.
 *
 * @param players a vector of player_t *
 * @param team the team to find the egg from
 */
player_t *hatch_team_egg(vector_t *players, team_t team);

/**
 * @brief Feed a line to a player. We have no fucking idea what the player is
 * doing right now, so you can pray for an answer but I can't promise nothing
 * THIS WILL COPY THE LINE INTO AN ALLOCATED ARRAY
 *
 * @param player the player to feed the line to
 * @param line the line to feed
 */
void feed_player_line(
    player_t *player, const char *line);

/**
 * @brief Feed a line to the GUI. As there is no waiting time for the commands
 * coming from the gui, you will find at least one answer in the log buffer
 * after calling this function.
 *
 * @param trantor a pointer to trantor
 * @param line the line to feed
 */
void gui_feed_trantor_line(trantor_t *trantor, const char *line);

/**
 * @brief Actualize the server app to now. Will decrement ongoing actions with
 * a delta time. Some actions might be triggered, and the corresponding buffers
 * (players and log) will be fed.
 *
 * @param trantor a pointer to trantor
 */
void trantor_time_pass(trantor_t *trantor);

/**
 * @brief returns the list of lines to send to a player
 */
vector_t *get_player_buffer(player_t *player);

/**
 * @brief returns the list of lines to send to the GUI
 */
vector_t *get_gui_buffer(trantor_t *trantor);
