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

    #define G1_P_SPEED 1.42
    #define G1_P_DIAG_SPEED 1
    #define G1_H_TO_W(x) ((uint16_t)((x) * 256))
    #define G1_SPEED (G1_H_TO_W(G1_P_SPEED))
    #define G1_DIAG_SPEED (G1_H_TO_W(G1_P_DIAG_SPEED))
    #define G1_NB_HEART 3

    #define G1_DASH_MULTI 3
    #define G1_DASH_COOLDOWN 150
    #define G1_DASH_TIME 10
    #define G1_DASH_DELTA_TIME (G1_DASH_COOLDOWN - G1_DASH_TIME)
    
typedef enum {
    GAME1_VRAM_PLAYER,
    GAME1_VRAM_HEART,
    GAME1_VRAM_FLASH,
    // GAME1_VRAM_SCORE,
    NB_GAME1_VRAM,
};

typedef enum {
    GAME1_PLAYER,
    GAME1_HEART1,
    GAME1_HEART2,
    GAME1_HEART3,
    GAME1_FLASH,
};

typedef struct {
    fixed x;
    fixed y;
    uint8_t vram_id;
    uint8_t nb_skins;
    heart_t hearts[G1_NB_HEART];
    uint8_t dash_timer;
    uint8_t flip;
} palyer_t;

typedef struct {
    uint8_t nb_vram;
    vram_sprite_t vram[NB_GAME1_VRAM];
    sprite_t sprites[MAX_SPRITE];
    uint8_t score;
    palyer_t player;
} g1_state;

    void g1_init(g1_state *game);
    game_state_t g1_update(g1_state *game,
        const input_state *input);

void g1_move_player(g1_state *game, const input_state *input);
void g1_handle_player(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock);
    
#endif
