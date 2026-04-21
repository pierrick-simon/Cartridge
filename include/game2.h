/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2 interface
*/

#ifndef GAME2_H
    #define GAME2_H

    #include "types.h"
#include "input.h"

typedef struct {
    uint8_t score;
} Game2State;

void game2Init(Game2State *game);
game_state_t game2Update(Game2State *game, const InputState *input);

#endif
