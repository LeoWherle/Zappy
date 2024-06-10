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
 * It contains the map, the players and the log buffer
 * server was updated.
 *
 * @param params the parameters of Trantor, see trantor/params.h
 * @param map the map of the server
 * @param players a vector of player_t *
 * @param log a vector of char * containing the log of the server, destined to
 * the GUI
 */
typedef struct trantor_s {
    trantor_params_t params;
    map_t map;
    vector_t players;
    string_t log;
    int winning_team;
    float since_spam;
    bool paused;
} trantor_t;

bool parse_args(int ac, char **av, trantor_params_t *params);
void init_trantor(trantor_t *trantor);
void free_trantor(trantor_t *trantor);


/**
 * @brief Destroy a player. This will free the player and remove it from the
 * players vector, as well as unlocking potential freezed players.
 *
 * @param trantor a pointer to trantor
 * @param player the player to destroy
 */
void remove_player(trantor_t *trantor, player_t *player);

/**
 * @brief Find an available unhatched egg from a team. Will return NULL if no
 * egg is found. This will hatch the egg and init necessary player fields.
 *
 * @param trantor a pointer to trantor
 * @param team the team name
 */
player_t *hatch_team_egg(trantor_t *trantor, const char *team_name);

/**
 * @brief Count the number of eggs from a team
 *
 * @param trantor a pointer to trantor
 * @param team_name the team name
 * @return unsigned int the number of eggs
 */
unsigned int count_team_egg(trantor_t *trantor, const char *team_name);

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
 * @brief Actualize the server app with delta. Will decrement ongoing actions
 * with a delta time. Some actions might be triggered, and the corresponding
 * buffers (players and log) will be fed.
 *
 * This will return true if trantor is still running, false when if game ended
 *
 * @param trantor a pointer to trantor
 * @param delta the time passed since last time
 * @param real_time if true, the delta will be multiplied by the server speed
 */
bool trantor_time_pass(trantor_t *trantor, float delta, bool real_time);

/**
 * @brief returns the list of lines to send to a player
 * please empty them, i'll not do it
 */
string_t *get_player_buffer(player_t *player);

/**
 * @brief returns the list of lines to send to the GUI
 * please empty them, i'll not do it
 */
string_t *get_gui_buffer(trantor_t *trantor);

/**
 * @brief pauses or unpauses the server, saving the multiplicatore di tempo
 */
void trantor_pause(trantor_t *trantor);


/**
 * @brief resets Trantor to its initial state
 */
void reset_trantor(trantor_t *trantor);


/**
 * @brief returns the time required for the next action to be executed
 */
float trantor_min_time(trantor_t *trantor);


// internal
void execute_gcmd(trantor_t *trantor, const char *gcmd);
unsigned int count_idxteam_egg(trantor_t *trantor, team_t t);
