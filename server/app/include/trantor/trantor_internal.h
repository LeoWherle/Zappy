/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** trantor internal header
*/

#pragma once

#include "trantor.h"
#include "trantor/player.h"

void execute_pcmd(trantor_t *trantor, player_t *player);
void execute_gcmd(trantor_t *trantor, const char *gcmd);
