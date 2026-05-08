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
    
    #define NB_AMMUNITION 3

    typedef enum {
        GAME2_SHIP1,
        GAME2_SHIP2,
        GAME2_AMMUNITION,
        NB_GAME2_SPRITE,
    };

    typedef enum {
        GAME2_THEME,
        GAME2_NB_MUSIC,
    };

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t sprite_id;
        uint8_t nb_sprite;
    } palyer_t;

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t sprite_id;
        uint8_t shoot;
    } ammunition_t;

    typedef struct {
        uint8_t score;
        uint8_t nb_sprites;
        vram_sprite_t vram[NB_GAME2_SPRITE];
        sprite_t sprites[MAX_SPRITE];
        sound_t musics[GAME2_NB_MUSIC];
        ammunition_t ammunitions[NB_AMMUNITION];
        palyer_t player;
        uint8_t bg_x;
        uint8_t bg_y;
    } Game2State;

    void game2Init(Game2State *game);
    game_state_t game2Update(Game2State *game,
        const InputState *input);

#endif
