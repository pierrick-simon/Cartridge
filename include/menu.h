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

    #define MENU_ENTRY_COUNT 3
    #define NB_GAME 3
    #define M_NB_NUMBER 5

    typedef enum {
        MENU_VRAM_CURSOR,
        MENU_VRAM_NUMBER,
        NB_MENU_VRAM,
    };

    typedef enum {
        MENU_CURSOR,
        MENU_SCORE1,
        MENU_SCORE2,
        MENU_SCORE3,
        MENU_SCORE4,
        MENU_SCORE5,
    };

    typedef enum {
        MENU_THEME,
        MENU_NB_MUSIC,
    };

    typedef struct {
        uint8_t cursor;
        uint8_t nb_vram;
        uint16_t scores[NB_GAME];
        vram_sprite_t vram[NB_MENU_VRAM];
        sprite_t sprites[MAX_SPRITE];
        sound_t musics[MENU_NB_MUSIC];
    } menu_state;

    void m_init(menu_state *menu);
    game_state_t m_update(menu_state *menu,
        const input_state *input);

#endif
