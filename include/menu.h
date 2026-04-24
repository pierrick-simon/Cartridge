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

    typedef struct {
        uint8_t cursor;
    } MenuState;

    void menuInit(MenuState *menu, sound_t *bgm);
    game_state_t menuUpdate(MenuState *menu,
        const InputState *input, sound_t *bgm);

#endif
