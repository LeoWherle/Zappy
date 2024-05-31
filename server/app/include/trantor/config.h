/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** common header
*/

#pragma once

#include "trantor/pcmd.h"
#include "trantor/pcmd_args.h"
#include "trantor/gcmd.h"

#define PCMD_COUNT 13
#define GCMD_COUNT 10
#define ITEM_COUNT 8
#define MAX_LEVEL 8

#define START_LIFE_UNITS 1260.0
#define FOOD_LIFE_UNIT 126.0
#define MAP_REFILLS_INTERVAL 20.0

typedef struct item_config_s {
    item_t type;
    const char *name;
    float density;
} item_config_t;

typedef struct pcmd_config_s {
    pcommand_t type;
    const char *name;
    unsigned int time;
    pcmd_func_t func;
} pcmd_config_t;

typedef struct elev_config_s {
    unsigned players;
    tile_t stones;
} elev_config_t;

typedef struct gcmd_config_s {
    gcommand_t type;
    const char *name;
    gcmd_func_t func;
} gcmd_config_t;

const char *get_item_name(item_t item);
size_t get_item_name_len(item_t item);
float get_item_density(item_t item);
item_t get_item_by_name(const char *name);

const char *get_pcmd_name(pcommand_t pcmd);
size_t get_pcmd_name_len(pcommand_t pcmd);
unsigned int get_pcmd_time(pcommand_t pcmd);
pcmd_func_t get_pcmd_func(pcommand_t pcmd);
pcommand_t get_pcmd_by_name(const char *name);

const char *get_gcmd_name(gcommand_t gcmd);
size_t get_gcmd_name_len(gcommand_t gcmd);
gcmd_func_t get_gcmd_func(gcommand_t gcmd);
gcommand_t get_gcmd_by_name(const char *name);

unsigned int get_elev_players(unsigned int level);
const tile_t *get_elev_stones(unsigned int level);
