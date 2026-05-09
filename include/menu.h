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

    #define MENU_ENTRY_COUNT 3

    typedef enum {
        MENU_THEME,
        MENU_NB_MUSIC,
    };

    typedef struct {
        uint8_t cursor;
        sound_t musics[MENU_NB_MUSIC];
    } menu_state;

    void m_init(menu_state *menu);
    game_state_t m_update(menu_state *menu,
        const input_state *input);

#endif
