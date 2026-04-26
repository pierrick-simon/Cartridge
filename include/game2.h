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
    #include "sprite.h"
    
    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t sprite_id;
        uint8_t nb_sprite;
    } palyer_t;

    typedef struct {
        uint8_t score;
        uint8_t nb_sprites;
        sprite_t sprites[40];
        palyer_t player;
    } Game2State;

    void game2Init(Game2State *game, sound_t bgm[NB_CHANNEL]);
    game_state_t game2Update(Game2State *game,
        const InputState *input, sound_t bgm[NB_CHANNEL]);

#endif
