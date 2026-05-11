/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** save
*/

#include <gb/gb.h>
#include "menu.h"
#include "save_data.h"

void load_save(uint16_t best_score[NB_GAME])
{
    ENABLE_RAM;
    best_score[0] = g1_best_score;
    best_score[1] = g2_best_score;
    best_score[2] = g3_best_score;
    DISABLE_RAM;
}

static uint16_t get_greater(uint16_t one, uint16_t two)
{
    if (one > two)
        return one;
    return two;
}

void save_score(uint16_t score, uint8_t game_id)
{
    ENABLE_RAM;
    saved_check_flag = CHECK_FLAG;
    if (game_id == 0)
        g1_best_score = get_greater(score, g1_best_score);
    else if (game_id == 1)
        g2_best_score = get_greater(score, g2_best_score);
    else
        g3_best_score = get_greater(score, g3_best_score);
    DISABLE_RAM;
}

void init_save_score(void)
{
    ENABLE_RAM;
    saved_check_flag = CHECK_FLAG;
    g1_best_score = 0;
    g2_best_score = 0;
    g3_best_score = 0;
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
