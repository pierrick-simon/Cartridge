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

    #define P_SPEED 1.42
    #define P_DIAG_SPEED 1
    #define BH_TO_W(x) ((uint16_t)(x * 256))
    #define SPEED ((uint16_t)(P_SPEED * 256))
    #define DIAG_SPEED ((uint16_t)(P_DIAG_SPEED * 256))
    
typedef struct {
    uint8_t score;
    fixed player_x;
    fixed player_y;
    uint8_t player_flip;
} Game1State;

void game1Init(Game1State *game);
game_state_t game1Update(Game1State *game, const InputState *input);

#endif
