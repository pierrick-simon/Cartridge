/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3 interface
*/

#ifndef GAME3_H
    #define GAME3_H

    #include "game_types.h"
    #include "input.h"
    #include "sound_manager.h"

    typedef struct {
        uint8_t score;
    } Game3State;

    void game3Init(Game3State *game, sound_t *bgm);
    game_state_t game3Update(Game3State *game,
        const InputState *input, sound_t *bgm);

#endif
