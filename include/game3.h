/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3 interface
*/

#ifndef GAME3_H
    #define GAME3_H

    #include <stdint.h>

    #include "game_types.h"
    #include "input.h"

    #define G3_NB_PLATFORMS 6
    #define G3_PLAT_TILE_IDX 8
    #define G3_PLAT_W 16
    #define G3_PLAT_H 8
    #define G3_PLAT_SPR_OFF 2
    #define G3_PLAYER_SPR 1
    #define G3_SCREEN_W 160
    #define G3_SCREEN_H 144
    #define G3_JUMP_VY (-11)
    #define G3_GRAVITY 1
    #define G3_MAX_VY 2
    #define G3_PLAYER_W 8
    #define G3_PLAYER_H 8
    #define G3_CAMERA_Y 56
    #define G3_PLAT_GAP_MIN 24
    #define G3_PLAT_GAP_MAX 40
    #define G3_PLAYER_SPEED 2

    typedef struct {
        uint8_t x;
        uint8_t y;
    } platform_t;

    typedef enum {
        G3_PLAY,
        G3_DEAD
    } g3_phase_t;

    typedef struct {
        uint8_t score;
        uint8_t px;
        uint8_t py;
        int8_t vx;
        int8_t vy;
        platform_t platforms[G3_NB_PLATFORMS];
        g3_phase_t phase;
        uint8_t rng;
    } Game3State;

    void game3Init(Game3State *game);
    game_state_t game3Update(Game3State *game,
        const InputState *input);

#endif /* !GAME3_H */
