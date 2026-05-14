/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3
*/

#include <gb/gb.h>
#include <stdio.h>
#include <rand.h>
#include "game3.h"
#include "input.h"
#include "playertile.h"
#include "platformtile.h"

static void initPlatforms(g3_state *game)
{
    game->platforms[0].x = 80;
    game->platforms[0].y = 144;
    game->platforms[1].x = 56;
    game->platforms[1].y = 116;
    game->platforms[2].x = 104;
    game->platforms[2].y = 92;
    game->platforms[3].x = 40;
    game->platforms[3].y = 68;
    game->platforms[4].x = 120;
    game->platforms[4].y = 44;
    game->platforms[5].x = 72;
    game->platforms[5].y = 20;
}

static void drawPlatforms(const g3_state *game)
{
    uint8_t i = 0;
    uint8_t sid;

    while (i < G3_NB_PLATFORMS) {
        sid = G3_PLAT_SPR_OFF + i * 2;
        if (rand() % 2 == 0) {
            set_sprite_tile(sid, G3_PLAT_TILE_IDX);
            set_sprite_tile(sid + 1, G3_PLAT_TILE_IDX + 1);
        } else {
            set_sprite_tile(sid, G3_PLAT_TILE_IDX + 1);
            set_sprite_prop(sid, S_FLIPX);
            set_sprite_tile(sid + 1, G3_PLAT_TILE_IDX);
            set_sprite_prop(sid + 1, S_FLIPX);
        }
        move_sprite(sid, game->platforms[i].x, game->platforms[i].y);
        move_sprite(sid + 1, game->platforms[i].x + 8, game->platforms[i].y);
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
    initPlatforms(game);
    set_sprite_data(1, 7, player_tile);
    set_sprite_tile(G3_PLAYER_SPR, 1);
    move_sprite(G3_PLAYER_SPR, game->px, game->py.b.h);
    set_sprite_data(G3_PLAT_TILE_IDX, PLATFORM_TILE_SIZE, platform_tile);
    drawPlatforms(game);
    SHOW_BKG;
    SHOW_SPRITES;
}

static inline uint8_t nextRng(uint8_t rng)
{
    return rng * 53 + 1;
}

static void recyclePlatform(g3_state *game, uint8_t i, uint8_t topy)
{
    game->rng = nextRng(game->rng);
    game->platforms[i].x =
        8 + (game->rng % (G3_SCREEN_W - G3_PLAT_W - 16));
    game->platforms[i].y = topy;
}

static void scrollWorld(g3_state *game, uint8_t delta)
{
    uint8_t i = 0;
    uint8_t sid;
    uint8_t top_y = 255;

    while (i < G3_NB_PLATFORMS) {
        game->platforms[i].y += delta;
        if (game->platforms[i].y < top_y)
            top_y = game->platforms[i].y;
        i++;
    }
    i = 0;
    while (i < G3_NB_PLATFORMS) {
        if (game->platforms[i].y > G3_SCREEN_H + 16) {
            game->rng = nextRng(game->rng);
            recyclePlatform(game, i, top_y - G3_PLAT_GAP_MIN
                - (game->rng % (G3_PLAT_GAP_MAX - G3_PLAT_GAP_MIN)));
            top_y = game->platforms[i].y;
        }
        sid = G3_PLAT_SPR_OFF + i * 2;
        move_sprite(sid, game->platforms[i].x, game->platforms[i].y);
        move_sprite(sid + 1, game->platforms[i].x + 8, game->platforms[i].y);
        i++;
    }
}

static void applyGravity(g3_state *game)
{
    uint8_t delta;

    game->vy += G3_GRAVITY;
    if (game->vy > G3_MAX_VY)
        game->vy = G3_MAX_VY;
    game->py.w = (uint16_t)((int16_t)game->py.w + game->vy);
    if (game->py.b.h < G3_CAMERA_Y && game->vy < 0) {
        delta = G3_CAMERA_Y - game->py.b.h;
        game->py.b.h = G3_CAMERA_Y;
        game->py.b.l = 0;
        scrollWorld(game, delta);
    }
}

static uint8_t landedOn(const g3_state *game, uint8_t i)
{
    uint8_t foot = game->py.b.h;
    uint8_t ptop = game->platforms[i].y;
    uint8_t pleft = game->platforms[i].x;

    if (game->vy <= 0 || foot == 0)
        return 0;
    if (foot < ptop - 5 || foot > ptop + 15)
        return 0;
    if (game->px + G3_PLAYER_W < pleft)
        return 0;
    if (game->px > pleft + G3_PLAT_W)
        return 0;
    return 1;
}

static void checkCollisions(g3_state *game)
{
    uint8_t i = 0;

    while (i < G3_NB_PLATFORMS) {
        if (landedOn(game, i)) {
            game->vy = G3_JUMP_VY;
            game->score++;
            return;
        }
        i++;
    }
}

static void moveHorizontal(g3_state *game, uint8_t held)
{
    if (held & J_LEFT) {
        if (game->px <= 8)
            game->px = 160;
        else
            game->px -= G3_PLAYER_SPEED;
    }
    if (held & J_RIGHT) {
        if (game->px >= 160)
            game->px = 8;
        else
            game->px += G3_PLAYER_SPEED;
    }
}

static inline void showGameOver(const g3_state *game)
{
    HIDE_SPRITES;
}

static game_state_t updateDead(g3_state *game,
    const input_state *input)
{
    uint8_t pressed = get_just_pressed(input);

    if (pressed & J_A) {
        g3_init(game);
        return STATE_GAME3;
    }
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME3;
}

static game_state_t updatePlay(g3_state *game,
    const input_state *input)
{
    uint8_t held = get_held(input);

    moveHorizontal(game, held);
    applyGravity(game);
    checkCollisions(game);
    move_sprite(G3_PLAYER_SPR, game->px, game->py.b.h);
    if (game->py.b.h > G3_SCREEN_H + 16) {
        game->phase = G3_DEAD;
        showGameOver(game);
    }
    if (get_just_pressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME3;
}

game_state_t g3_update(g3_state *game,
    const input_state *input)
{
    if (game->phase == G3_DEAD)
        return updateDead(game, input);
    return updatePlay(game, input);
}
