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
    #include <asm/types.h>

    #define G1_P_SPEED 1.42
    #define G1_P_DIAG_SPEED 1
    #define G1_H_TO_W(x) ((uint16_t)((x) * 256))
    #define G1_SPEED (G1_H_TO_W(G1_P_SPEED))
    #define G1_DIAG_SPEED (G1_H_TO_W(G1_P_DIAG_SPEED))

    #define G1_DASH_MULTI 3
    #define G1_DASH_COOLDOWN 180
    #define G1_DASH_TIME 10
    #define G1_DELTA_DASH 15
    #define G1_DASH_DELTA_TIME (G1_DASH_COOLDOWN - G1_DASH_TIME)

    #define ABS(x) ((x) >= 0 ? x : (x * -1))

    #define G1_X 1
    #define G1_Y 2

    #define G1_CD_TIMER 250
    #define G1_CD_DELTA 8
    
    #define G1_NB_ASTEROID 10
    #define G1_NB_HEART 3
    #define G1_NB_SCORE 4

typedef enum {
    GAME1_VRAM_PLAYER,
    GAME1_VRAM_HEART,
    GAME1_VRAM_FLASH,
    GAME1_VRAM_SCORE,
    GAME1_VRAM_ASTEROID,
    NB_GAME1_VRAM,
};

typedef enum {
    // player
    GAME1_PLAYER,

    // gui
    GAME1_F_HEART,
    GAME1_L_HEART = GAME1_F_HEART + G1_NB_HEART - 1,
    GAME1_FLASH,
    GAME1_F_SCORE,
    GAME1_L_SCORE = GAME1_F_SCORE + G1_NB_SCORE - 1,

    // attacks
    GAME1_F_ASTEROID,
    GAME1_L_ASTEROID = GAME1_F_ASTEROID + G1_NB_ASTEROID - 1,
};

typedef struct {
    uint8_t x;
    uint8_t y;
    int8_t v_x;
    int8_t v_y;
    uint8_t speed;
    uint16_t timer;
    uint8_t orientation;
    uint8_t here;
} asteroid_t;

typedef struct {
    fixed x;
    fixed y;
    uint8_t nb_skins;
    heart_t hearts[G1_NB_HEART];
    uint8_t dash_timer;
    uint8_t cd_timer;
    uint8_t flip;
} palyer_t;

typedef struct {
    uint8_t nb_vram;
    vram_sprite_t vram[NB_GAME1_VRAM];
    sprite_t sprites[MAX_SPRITE];
    uint16_t score;
    palyer_t player;
    asteroid_t asteroid[G1_NB_ASTEROID];
} g1_state;

    void g1_init(g1_state *game);
    game_state_t g1_update(g1_state *game,
        const input_state *input);

void g1_move_player(g1_state *game, const input_state *input);
void g1_handle_player(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock);
void g1_change_score(g1_state *game, uint8_t gain);
void g1_handle_attacks(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock);
void change_nb_live(palyer_t *player, uint8_t gain);

#endif
