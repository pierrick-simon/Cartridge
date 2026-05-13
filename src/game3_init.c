/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3 initialization
*/

#include <gb/gb.h>
#include "game3.h"
#include "playertile.h"
#include "platformtile.h"
#include "hearttile.h"
#include "number.h"
#include "moontile.h"
#include "game2_theme.h"

void g3_initPlatforms(g3_state *game)
{
    game->platforms[0].x = 80; game->platforms[0].y = 144; game->platforms[0].vx = 0;
    game->platforms[1].x = 56; game->platforms[1].y = 116; game->platforms[1].vx = 0;
    game->platforms[2].x = 104; game->platforms[2].y = 92; game->platforms[2].vx = 0;
    game->platforms[3].x = 40; game->platforms[3].y = 68; game->platforms[3].vx = 0;
    game->platforms[4].x = 120; game->platforms[4].y = 44; game->platforms[4].vx = 0;
    game->platforms[5].x = 72; game->platforms[5].y = 20; game->platforms[5].vx = 0;
}

void g3_drawPlatforms(const g3_state *game)
{
    uint8_t i = 0;
    uint8_t sid;

    while (i < G3_NB_PLATFORMS) {
        sid = G3_PLAT_SPR_OFF + i * 2;
        set_sprite_tile(sid, G3_PLAT_TILE_IDX);
        set_sprite_tile(sid + 1, G3_PLAT_TILE_IDX);
        move_sprite(sid, game->platforms[i].x, game->platforms[i].y);
        move_sprite(sid + 1, game->platforms[i].x + 8, game->platforms[i].y);
        i++;
    }
}

static void initSounds(g3_state *game)
{
    game->bounce_sfx.state = SND_OFF;
    game->bounce_sfx.music = NULL;
    sound_start(&game->theme, 3, game2_theme_music, 1, 0x80);
}

static void initBackground(void)
{
    set_bkg_data(0, 0, moon_tile);
    set_bkg_tiles(0, 0, 20, 18, moon_map);
}

static void initVram(void)
{
    set_sprite_data(1, P_NB_SPRITE, player_tile);
    set_sprite_data(G3_PLAT_TILE_IDX, PLATFORM_TILE_SIZE, platform_tile);
    set_sprite_data(G3_NUMBER_VRAM_IDX, NUMBER_SIZE, number_tiles);
    set_sprite_data(G3_HEART_VRAM_IDX, HEART_SIZE, heart_tiles);
}

static void initScore(void)
{
    uint8_t i = 0;

    while (i < G3_NB_NUMBER) {
        set_sprite_tile(G3_SCORE_SPR_OFF + i, G3_NUMBER_VRAM_IDX);
        move_sprite(G3_SCORE_SPR_OFF + i, 8 + 6 * i, G3_HUD_Y);
        i++;
    }
}

static void initHearts(g3_state *game)
{
    uint8_t i = 0;

    while (i < G3_NB_HEART) {
        game->hearts[i].show = 1;
        game->hearts[i].x = 160 - 10 * G3_NB_HEART + 10 * i;
        game->hearts[i].y = G3_HUD_Y;
        set_sprite_tile(G3_HEART_SPR_OFF + i, G3_HEART_VRAM_IDX);
        move_sprite(G3_HEART_SPR_OFF + i,
            game->hearts[i].x, game->hearts[i].y);
        i++;
    }
}

void g3_init(g3_state *game)
{
    game->score = 0;
    game->phase = G3_PLAY;
    game->rng = DIV_REG;
    game->px = 88;
    game->py.w = 0;
    game->py.b.h = 128;
    game->vx = 0;
    game->vy = G3_JUMP_VY;
    game->anim_timer = 0;
    initSounds(game);
    g3_initPlatforms(game);
    initBackground();
    initVram();
    set_sprite_tile(G3_PLAYER_SPR, 1 + P_IDLE);
    move_sprite(G3_PLAYER_SPR, game->px, game->py.b.h);
    g3_drawPlatforms(game);
    initScore();
    initHearts(game);
    SHOW_BKG;
    SHOW_SPRITES;
}
