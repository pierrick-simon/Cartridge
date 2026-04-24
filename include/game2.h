/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2 interface
*/

#ifndef GAME2_H
    #define GAME2_H

    #include "game_types.h"
    #include "input.h"
    #include "sound_manager.h"

    typedef struct {
        uint8_t score;
    } Game2State;

    void game2Init(Game2State *game, sound_t bgm[NB_CHANNEL]);
    game_state_t game2Update(Game2State *game,
        const InputState *input, sound_t bgm[NB_CHANNEL]);

#endif
