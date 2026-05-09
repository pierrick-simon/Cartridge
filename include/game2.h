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
    #include "heart.h"
    
    #define NB_AMMUNITION 3
    #define NB_ENEMY 15
    #define NB_ENEMY_SKIN 2
    #define NB_SKIN 2
    #define NB_HEART 3
    #define NB_NUMBER 5

    typedef enum {
        GAME2_VRAM_SHIP1,
        GAME2_VRAM_SHIP2,
        GAME2_VRAM_SHIP3,
        GAME2_VRAM_SHIP4,
        GAME2_VRAM_AMMUNITION,
        GAME2_VRAM_EXPLOSION,
        GAME2_VRAM_HEART,
        GAME2_VRAM_SCORE,
        NB_GAME2_VRAM,
    };

    typedef enum {
        GAME2_PLAYER,
        GAME2_AMMUNITION1,
        GAME2_AMMUNITION2,
        GAME2_AMMUNITION3,
        GAME2_ENEMY1,
        GAME2_ENEMY2,
        GAME2_ENEMY3,
        GAME2_ENEMY4,
        GAME2_ENEMY5,
        GAME2_ENEMY6,
        GAME2_ENEMY7,
        GAME2_ENEMY8,
        GAME2_ENEMY9,
        GAME2_ENEMY10,
        GAME2_ENEMY11,
        GAME2_ENEMY12,
        GAME2_ENEMY13,
        GAME2_ENEMY14,
        GAME2_ENEMY15,
        GAME2_HEART1,
        GAME2_HEART2,
        GAME2_HEART3,
        GAME2_SCORE1,
        GAME2_SCORE2,
        GAME2_SCORE3,
        GAME2_SCORE4,
        GAME2_SCORE5,
    };

    typedef enum {
        GAME2_THEME,
        GAME2_POWER_UP,
        GAME2_POWER_DOWN,
        GAME2_NB_MUSIC,
    };

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t vram_id;
        uint8_t show;
        uint8_t explode;
    } enemy_t;

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t vram_id;
        uint8_t shoot;
    } ammunition_t;

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t vram_id;
        uint8_t nb_skins;
        heart_t hearts[NB_HEART];
    } player_t;

    typedef struct {
        uint8_t score;
        uint8_t nb_vram;
        vram_sprite_t vram[NB_GAME2_VRAM];
        sprite_t sprites[MAX_SPRITE];
        sound_t musics[GAME2_NB_MUSIC];
        ammunition_t ammunitions[NB_AMMUNITION];
        enemy_t enemies[NB_ENEMY];
        player_t player;
        uint8_t bg_x;
        uint8_t bg_y;
    } Game2State;

    void game2Init(Game2State *game);
    game_state_t game2Update(Game2State *game,
        const InputState *input);

    void handle_enemies(Game2State *game, uint8_t clock);
    void handle_ammunition(Game2State *game, uint8_t pressed);
    void handle_player(Game2State *game, const InputState *input,
        uint8_t pressed, uint8_t clock);

#endif
