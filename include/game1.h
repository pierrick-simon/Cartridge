/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1 interface
*/

#ifndef GAME1_H
    #define GAME1_H

    #include "game_types.h"
    #include "input.h"
    #include "sound_manager.h"

    typedef struct {
        uint8_t score;
        uint8_t player_x;
        uint8_t player_y;
    } Game1State;

    void game1Init(Game1State *game, sound_t *bgm);
    game_state_t game1Update(Game1State *game,
        const InputState *input, sound_t *bgm);

#endif
