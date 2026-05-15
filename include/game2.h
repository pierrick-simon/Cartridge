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
    
    #define G2_NB_AMMUNITION 6
    #define G2_NB_ENEMY 5
    #define G2_NB_ENEMY_SKIN 2
    #define G2_NB_SKIN 2
    #define G2_NB_HEART 5
    #define G2_NB_NUMBER 4
    #define G2_NB_ENEMIES_AMMUNITION 10
    #define G2_NB_POWER_UP 3
    #define G2_ENEMY_SHOOT_DELAY 90

    #define G2_INVINCIBLE_FRAMES 90

    typedef enum {
        GAME2_VRAM_SHIP1,
        GAME2_VRAM_SHIP2,
        GAME2_VRAM_SHIP3,
        GAME2_VRAM_SHIP4,
        GAME2_VRAM_AMMUNITION,
        GAME2_VRAM_EXPLOSION,
        GAME2_VRAM_HEART,
        GAME2_VRAM_SCORE,
        GAME2_VRAM_POWER_UP,
        NB_GAME2_VRAM,
    };

    typedef enum {
        GAME2_PLAYER,
        GAME2_AMMUNITION1,
        GAME2_AMMUNITION2,
        GAME2_AMMUNITION3,
        GAME2_AMMUNITION4,
        GAME2_AMMUNITION5,
        GAME2_AMMUNITION6,
        GAME2_ENEMY1,
        GAME2_ENEMY2,
        GAME2_ENEMY3,
        GAME2_ENEMY4,
        GAME2_ENEMY5,
        GAME2_ENEMY6,
        GAME2_ENEMY7,
        GAME2_ENEMIES_AMMUNITION1,
        GAME2_ENEMIES_AMMUNITION2,
        GAME2_ENEMIES_AMMUNITION3,
        GAME2_ENEMIES_AMMUNITION4,
        GAME2_ENEMIES_AMMUNITION5,
        GAME2_ENEMIES_AMMUNITION6,
        GAME2_ENEMIES_AMMUNITION7,
        GAME2_ENEMIES_AMMUNITION8,
        GAME2_ENEMIES_AMMUNITION9,
        GAME2_ENEMIES_AMMUNITION10,
        GAME2_HEART1,
        GAME2_HEART2,
        GAME2_HEART3,
        GAME2_HEART4,
        GAME2_HEART5,
        GAME2_SCORE1,
        GAME2_SCORE2,
        GAME2_SCORE3,
        GAME2_SCORE4,
        GAME2_POWER_UP1,
        GAME2_POWER_UP2,
        GAME2_POWER_UP3,
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
        uint8_t timer;
        uint8_t dir;
        uint8_t move_timer;
    } enemy_t;

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t vram_id;
        uint8_t show;
    } entity_t;

    typedef struct {
        uint8_t x;
        uint8_t y;
        uint8_t vram_id;
        uint8_t nb_skins;
        uint8_t invincible;
        heart_t hearts[G2_NB_HEART];
    } player_t;

    typedef enum {
        G2_PLAY,
        G2_DEAD
    } g2_phase_t;

    typedef struct {
        uint16_t score;
        uint8_t nb_vram;
        vram_sprite_t vram[NB_GAME2_VRAM];
        sprite_t sprites[MAX_SPRITE];
        sound_t musics[GAME2_NB_MUSIC];
        entity_t ammunitions[G2_NB_AMMUNITION];
        entity_t enemies_ammunitions[G2_NB_ENEMIES_AMMUNITION];
        enemy_t enemies[G2_NB_ENEMY];
        entity_t power_up[G2_NB_POWER_UP];
        player_t player;
        uint8_t bg_x;
        uint8_t bg_y;
        g2_phase_t phase;
    } g2_state;

    void g2_init(g2_state *game);
    game_state_t g2_update(g2_state *game,
        const input_state *input);

    void g2_handle_enemies_ammunition(g2_state *game);
    void g2_handle_enemies(g2_state *game, uint16_t clock);
    void g2_handle_ammunition(g2_state *game, uint8_t pressed);
    uint8_t g2_handle_player(g2_state *game, const input_state *input,
        uint16_t clock);
    void g2_change_score(g2_state *game, uint8_t gain);
    void g2_change_nb_live(g2_state *game, uint8_t gain);
    void g2_handle_power_up(g2_state *game);

#endif