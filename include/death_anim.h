/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** death_anim
*/

#ifndef DEATH_ANIM_H_
    #define DEATH_ANIM_H_

    #include "input.h"

    #define DA_TILE_BASE 240
    #define DA_NB_TILES 8
    #define DA_CURTAIN_FRAMES 36
    #define DA_CURTAIN_STEP 4
    #define DA_TEXT_ROW 8

    typedef enum {
        DA_RUNNING,
        DA_RESTART,
        DA_MENU
    } da_result_t;

    void death_anim_start(void);
    da_result_t death_anim_update(const input_state *input);

#endif /* DEATH_ANIM_H_ */
