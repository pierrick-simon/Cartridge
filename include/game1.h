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
    #include "sprite.h"
    #include "heart.h"

    #define P_SPEED 1.42
    #define P_DIAG_SPEED 1
    #define H_TO_W(x) ((uint16_t)((x) * 256))
    #define SPEED (H_TO_W(P_SPEED))
    #define DIAG_SPEED (H_TO_W(P_DIAG_SPEED))
    #define NB_HEART 3

    #define DASH_MULTI 3
    #define DASH_COOLDOWN 150
    #define DASH_TIME 10
    #define DASH_DELTA_TIME (DASH_COOLDOWN - DASH_TIME)
    
typedef enum {
    GAME1_VRAM_PLAYER,
    // GAME1_VRAM_HEART,
    // GAME1_VRAM_SCORE,
    NB_GAME1_VRAM,
};

typedef enum {
    GAME1_PLAYER,
};

typedef struct {
    fixed x;
    fixed y;
    uint8_t vram_id;
    uint8_t nb_skins;
    heart_t hearts[NB_HEART];
    uint8_t dash_timer;
    uint8_t flip;
} palyer_t;

typedef struct {
    uint8_t nb_vram;
    vram_sprite_t vram[NB_GAME1_VRAM];
    sprite_t sprites[MAX_SPRITE];
    uint8_t score;
    palyer_t player;
} Game1State;

    void game1Init(Game1State *game);
    game_state_t game1Update(Game1State *game,
        const InputState *input);

void move_player(Game1State *game, const InputState *input);

#endif
