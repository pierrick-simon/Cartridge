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

    typedef struct {
        uint8_t score;
    } Game3State;

    void game3Init(Game3State *game);
    game_state_t game3Update(Game3State *game,
        const InputState *input);

#endif
