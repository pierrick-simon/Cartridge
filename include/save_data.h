/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** save_data
*/

#ifndef SAVE_DATA_H
    #define SAVE_DATA_H

    #include <gb/gb.h>

    #define CHECK_FLAG 54321
    #define NB_SAVE_SCORE 3

    extern uint16_t saved_check_flag;
    extern uint16_t g1_best_score[NB_SAVE_SCORE];
    extern uint16_t g2_best_score[NB_SAVE_SCORE];
    extern uint16_t g3_best_score[NB_SAVE_SCORE];

    void load_save(uint16_t best_score[3][NB_SAVE_SCORE]);
    void save_score(uint16_t score, uint8_t game_id);
    uint8_t has_existing_save(void);
    void init_save_score(void);

#endif
