/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** gui commands header
*/

#pragma once

#include "trantor.h"

#define USES_N(cmd) (cmd == PPO_GCMD || cmd == PLV_GCMD || cmd == PIN_GCMD)

typedef enum gcommand_e {
    NONE_GCMD = 0,
    MSZ_GCMD = 1,
    BCT_GCMD = 2,
    MCT_GCMD = 3,
    TNA_GCMD = 4,
    PPO_GCMD = 5,
    PLV_GCMD = 6,
    PIN_GCMD = 7,
    SGT_GCMD = 8,
    SST_GCMD = 9
} gcommand_t;

typedef union gcmd_args_u {
    len_t pos[2];
    unsigned int n;
    float t;
} gcmd_args_t;

typedef void (*gcmd_func_t)(trantor_t *trantor, gcmd_args_t *args);

void gui_error(trantor_t *trantor, gcmd_args_t *args);
void gui_msz(trantor_t *trantor, gcmd_args_t *args);
void gui_bct(trantor_t *trantor, gcmd_args_t *args);
void gui_mct(trantor_t *trantor, gcmd_args_t *args);
void gui_tna(trantor_t *trantor, gcmd_args_t *args);
void gui_ppo(trantor_t *trantor, gcmd_args_t *args);
void gui_plv(trantor_t *trantor, gcmd_args_t *args);
void gui_pin(trantor_t *trantor, gcmd_args_t *args);
void gui_sgt(trantor_t *trantor, gcmd_args_t *args);
void gui_sst(trantor_t *trantor, gcmd_args_t *args);
gcommand_t parse_gcmd(const char *gcmd, gcmd_args_t *args);
