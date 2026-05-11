/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** save_data
*/

#ifndef SAVE_DATA_H
    #define SAVE_DATA_H

    #include <gb/gb.h>
    #include "menu.h"

    #define CHECK_FLAG 12345

    extern uint16_t saved_check_flag;
    extern uint16_t g1_best_score;
    extern uint16_t g2_best_score;
    extern uint16_t g3_best_score;

    void load_save(uint16_t best_score[NB_GAME]);
    void save_score(uint16_t score, uint8_t game_id);
    uint8_t has_existing_save(void);
    void init_save_score(void);

#endif
