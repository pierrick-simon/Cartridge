/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** save
*/

#include <gb/gb.h>
#include "save_data.h"

void load_save(uint16_t best_score[3][NB_SAVE_SCORE])
{
    ENABLE_RAM;
    for (uint8_t i = 0; i < NB_SAVE_SCORE; i++) {
        best_score[0][i] = g1_best_score[i];
        best_score[1][i] = g2_best_score[i];
        best_score[2][i] = g3_best_score[i];
    }
    DISABLE_RAM;
}

static void save_greater(uint16_t score, uint16_t two[NB_SAVE_SCORE])
{
    uint16_t tmp = 0;
    uint16_t save = 0;
    uint8_t move = 0;

    for (uint8_t i = 0; i < NB_SAVE_SCORE; i++) {
        save = tmp;
        tmp = two[i];
        if (move == 1) {
            two[i] = save;
            continue;
        }
        if (tmp < score) {
            move = 1;
            two[i] = score;
        }
    }
}

void save_score(uint16_t score, uint8_t game_id)
{
    ENABLE_RAM;
    saved_check_flag = CHECK_FLAG;
    if (game_id == 0)
        save_greater(score, g1_best_score);
    else if (game_id == 1)
        save_greater(score, g2_best_score);
    else
        save_greater(score, g3_best_score);
    DISABLE_RAM;
}

void init_save_score(void)
{
    ENABLE_RAM;
    saved_check_flag = CHECK_FLAG;
    for (uint8_t i = 0; i < 3; i++) {
        g1_best_score[i] = 0;
        g2_best_score[i] = 0;
        g3_best_score[i] = 0;
    }
    DISABLE_RAM;
}

uint8_t has_existing_save(void)
{

    uint8_t saveDataExists = FALSE;
    
    ENABLE_RAM;
    saveDataExists = saved_check_flag == CHECK_FLAG;
    DISABLE_RAM;
    return saveDataExists;
}
