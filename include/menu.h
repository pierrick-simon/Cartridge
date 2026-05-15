/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Main menu interface
*/

#ifndef MENU_H
    #define MENU_H

    #include <stdint.h>
    #include "game_types.h"
    #include "input.h"
    #include "sound_manager.h"
    #include "sprite.h"
    #include "save_data.h"

    #define MENU_ENTRY_COUNT 3
    #define NB_GAME 3
    #define M_NB_NUMBER 5
    #define M_NB_TOTAL_NUMBER (M_NB_NUMBER * NB_SAVE_SCORE)

    typedef enum {
        MENU_VRAM_CURSOR,
        MENU_VRAM_NUMBER,
        NB_MENU_VRAM,
    };

    typedef enum {
        MENU_CURSOR,
        MENU_F_SCORE1,
        MENU_L_SCORE1 = MENU_F_SCORE1 + M_NB_NUMBER - 1,
        MENU_F_SCORE2,
        MENU_L_SCORE2 = MENU_F_SCORE2 + M_NB_NUMBER - 1,
        MENU_F_SCORE3,
        MENU_L_SCORE3 = MENU_F_SCORE3 + M_NB_NUMBER - 1,
    };

    typedef enum {
        MENU_THEME,
        MENU_NB_MUSIC,
    };

    typedef struct {
        uint8_t cursor;
        uint8_t nb_vram;
        uint16_t scores[NB_GAME][NB_SAVE_SCORE];
        vram_sprite_t vram[NB_MENU_VRAM];
        sprite_t sprites[MAX_SPRITE];
        sound_t musics[MENU_NB_MUSIC];
    } menu_state;

    void m_init(menu_state *menu);
    game_state_t m_update(menu_state *menu,
        const input_state *input);

#endif
