/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player commands exec header
*/

#pragma once

#include "trantor/pcmd.h"

typedef struct pcmd_executor_s {
    pcommand_t command;
    char *arg;
    item_t item;
    float exec_time_left;
} pcmd_executor_t;


pcmd_executor_t *create_pcmd_executor(const char *pcmd, float f);
