/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** game2_handle
*/

#include <gb/gb.h>
#include <rand.h>
#include "game2.h"
#include "input.h"

void change_score(Game2State *game, uint8_t gain)
{
    uint16_t score;

    game->score += gain;
    score = game->score;
    move_to_tile(&game->sprites[GAME2_SCORE5], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE4], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE3], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE2], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE1], game->vram, score % 10);
}

void change_nb_live(Game2State *game, uint8_t gain)
{
    uint8_t last = 0;

    for (uint8_t i = 0; i < NB_HEART; i++) {
        if (gain == 0 && game->player.hearts[i].show == 1) {
            game->player.hearts[i].show = 0;
            return;
        }
        if (gain == 1 && game->player.hearts[i].show == 1)
            break;
        last = i;
    }
    if (gain == 1)
        game->player.hearts[last].show = 1;
}

static void change_ship(Game2State *game, uint8_t pressed)
{
    if (pressed & J_DOWN) {
        reset_sound(&game->musics[GAME2_POWER_DOWN]);
        change_nb_live(game, 0);
    }
    if (!(pressed & J_UP))
        return;
    reset_sound(&game->musics[GAME2_POWER_UP]);
    game->player.vram_id++;
    if (game->player.vram_id >= game->player.nb_skins)
        game->player.vram_id = 0;
    init_sprite(game->player.vram_id, GAME2_PLAYER, game->sprites, game->vram);
    move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
    change_nb_live(game, 1);
}

static void move_everything(Game2State *game, uint8_t value)
{
    if (value > 2)
        game->bg_x++;
    else
        game->bg_x--;
    for (uint8_t i = 0; i < NB_AMMUNITION; i++) {
        if (game->ammunitions[i].shoot == 0)
            continue;
        game->ammunitions[i].x += value;
    }
    for (uint8_t i = 0; i < NB_ENEMY; i++) {
        if (game->enemies[i].show == 0)
            continue;
        game->enemies[i].x += value;
    }
    for (uint8_t i = 0; i < NB_ENEMIES_AMMUNITION; i++) {
        if (game->enemies_ammunitions[i].shoot == 0)
            continue;
        game->enemies_ammunitions[i].x += value;
    }
}

static void handle_heart(Game2State *game, uint16_t clock, uint8_t i)
{
    if (game->player.hearts[i].show == 0) {
        if (game->sprites[GAME2_HEART1 + i].current
            != game->vram[GAME2_VRAM_HEART].end - 1 && (clock & 1) == 0)
            move_up_sprite(&game->sprites[GAME2_HEART1 + i], game->vram);
        if (game->sprites[GAME2_HEART1 + i].current
            == game->vram[GAME2_VRAM_HEART].end - 1)
            hide_sprite(&game->sprites[GAME2_HEART1 + i]);
    } else {
        if (game->sprites[GAME2_HEART1 + i].current
            != game->vram[GAME2_VRAM_HEART].start && (clock & 1) == 0) {
            move_sprite(GAME2_HEART1 + i,
                game->player.hearts[i].x, game->player.hearts[i].y);
            move_down_sprite(&game->sprites[GAME2_HEART1 + i], game->vram);
        }
    }
}

void handle_player(Game2State *game, const InputState *input,
    uint8_t pressed, uint16_t clock)
{
    if ((clock & 3) == 0)
        move_up_sprite(&game->sprites[GAME2_PLAYER], game->vram);
    change_ship(game, pressed);
    if (getHeld(input) & J_LEFT) {
        game->player.x--;
        if (game->player.x < 16)
            game->player.x = 16;
        move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
        move_everything(game, 1);
    }
    if (getHeld(input) & J_RIGHT) {
        game->player.x++;
        if (game->player.x > 160 - 8)
            game->player.x = 160 - 8;
        move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
        move_everything(game, -1);
    }
    for (uint8_t i = 0; i < NB_HEART; i++)
        handle_heart(game, clock, i);
}

static uint8_t shoot(Game2State *game, uint8_t id)
{
    if (game->ammunitions[id].shoot == 1)
        return 0;
    game->ammunitions[id].shoot = 1;
    game->ammunitions[id].x = game->player.x;
    game->ammunitions[id].y = game->player.y;
    sound_channel1(0x2A, 0x80, 0xF1, 0xA9, 0x87);
    return 1;
}

void handle_ammunition(Game2State *game, uint8_t pressed)
{
    uint8_t launch = 0;

    for (uint8_t i = 0; i < NB_AMMUNITION; i++) {
        if ((pressed & J_A) && launch == 0)
            launch = shoot(game, i);
        if (game->ammunitions[i].shoot == 1) {
            game->ammunitions[i].y -= 2;
            move_sprite(GAME2_AMMUNITION1 + i,
                game->ammunitions[i].x, game->ammunitions[i].y);
            move_up_sprite(&game->sprites[GAME2_AMMUNITION1 + i], game->vram);
        }
        if (game->ammunitions[i].y <= 0)
            game->ammunitions[i].shoot = 0;
    }
}
