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

    #define P_SPEED 1.42
    #define P_DIAG_SPEED 1
    #define H_TO_W(x) ((uint16_t)((x) * 256))
    #define SPEED (H_TO_W(P_SPEED))
    #define DIAG_SPEED (H_TO_W(P_DIAG_SPEED))

    #define DASH_MULTI 3
    #define DASH_COOLDOWN 150
    #define DASH_TIME 10
    #define DASH_DELTA_TIME (DASH_COOLDOWN - DASH_TIME)
    
typedef struct {
    uint8_t score;
    fixed player_x;
    fixed player_y;
    uint8_t player_flip;
    uint8_t dash_timer;
} Game1State;

    void game1Init(Game1State *game, sound_t bgm[NB_CHANNEL]);
    game_state_t game1Update(Game1State *game,
        const InputState *input, sound_t bgm[NB_CHANNEL]);

void move_player(Game1State *game, const InputState *input);

#endif
