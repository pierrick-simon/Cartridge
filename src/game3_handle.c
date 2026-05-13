/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3 game logic and update
*/

#include <gb/gb.h>
#include "game3.h"
#include "input.h"
#include "playertile.h"
#include "save_data.h"

static void g3_update_score(const g3_state *game)
{
    uint16_t score = game->score;

    set_sprite_tile(G3_SCORE_SPR_OFF + 4, G3_NUMBER_VRAM_IDX + score % 10);
    score /= 10;
    set_sprite_tile(G3_SCORE_SPR_OFF + 3, G3_NUMBER_VRAM_IDX + score % 10);
    score /= 10;
    set_sprite_tile(G3_SCORE_SPR_OFF + 2, G3_NUMBER_VRAM_IDX + score % 10);
    score /= 10;
    set_sprite_tile(G3_SCORE_SPR_OFF + 1, G3_NUMBER_VRAM_IDX + score % 10);
    score /= 10;
    set_sprite_tile(G3_SCORE_SPR_OFF + 0, G3_NUMBER_VRAM_IDX + score % 10);
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
        g3_scrollWorld(game, delta);
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
            game->anim_timer = G3_ANIM_BOUNCE_FRAMES;
            sound_start(&game->bounce_sfx, 2, g3_bounce_snd, 0, 0xFF);
            return;
        }
        i++;
    }
}

static void moveHorizontal(g3_state *game, uint8_t held)
{
    if (held & J_LEFT) {
        set_sprite_prop(G3_PLAYER_SPR, S_FLIPX);
        if (game->px <= 8)
            game->px = 160;
        else
            game->px -= G3_PLAYER_SPEED;
    }
    if (held & J_RIGHT) {
        set_sprite_prop(G3_PLAYER_SPR, 0);
        if (game->px >= 160)
            game->px = 8;
        else
            game->px += G3_PLAYER_SPEED;
    }
}

static void hideGameplaySprites(void)
{
    uint8_t i = 0;

    move_sprite(G3_PLAYER_SPR, 0, 0);
    while (i < G3_NB_PLATFORMS) {
        move_sprite(G3_PLAT_SPR_OFF + i * 2, 0, 0);
        move_sprite(G3_PLAT_SPR_OFF + i * 2 + 1, 0, 0);
        i++;
    }
}

static void showGameOver(const g3_state *game)
{
    save_score(game->score, 2);
    hideGameplaySprites();
}

static void updatePlayerSprite(g3_state *game)
{
    if (game->anim_timer > 0) {
        game->anim_timer--;
        set_sprite_tile(G3_PLAYER_SPR, 1 + P_RL);
    } else {
        set_sprite_tile(G3_PLAYER_SPR, 1 + P_IDLE);
    }
    move_sprite(G3_PLAYER_SPR, game->px, game->py.b.h);
}

game_state_t updateDead(g3_state *game, const input_state *input)
{
    uint8_t pressed = getJustPressed(input);

    sound_update(&game->theme);
    if (pressed & J_A) {
        g3_init(game);
        return STATE_GAME3;
    }
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME3;
}

game_state_t updatePlay(g3_state *game, const input_state *input)
{
    uint8_t held = getHeld(input);

    moveHorizontal(game, held);
    applyGravity(game);
    g3_movePlatforms(game);
    checkCollisions(game);
    g3_update_score(game);
    sound_update(&game->theme);
    sound_update(&game->bounce_sfx);
    updatePlayerSprite(game);
    if (game->py.b.h > G3_SCREEN_H + 16) {
        game->phase = G3_DEAD;
        showGameOver(game);
    }
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME3;
}
