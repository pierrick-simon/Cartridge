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

void g2_change_score(g2_state *game, uint8_t gain)
{
    uint16_t score;

    game->score += gain;
    score = game->score;
    move_to_tile(&game->sprites[GAME2_SCORE4], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE3], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE2], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME2_SCORE1], game->vram, score % 10);
}

void g2_change_nb_live(g2_state *game, uint8_t gain)
{
    uint8_t last = 0;

    for (uint8_t i = 0; i < G2_NB_HEART; i++) {
        if (gain == 0 && game->player.hearts[i].show == 1
            && game->player.invincible == 0) {
            game->player.hearts[i].show = 0;
            game->player.invincible = G2_INVINCIBLE_FRAMES;
            reset_sound(&game->musics[GAME2_POWER_DOWN]);
            return;
        }
        if (gain == 1 && game->player.hearts[i].show == 1) {
            reset_sound(&game->musics[GAME2_POWER_UP]);
            break;
        }
        last = i;
    }
    if (gain == 1)
        game->player.hearts[last].show = 1;        
}

static void change_ship(g2_state *game)
{
    game->player.vram_id++;
    if (game->player.vram_id >= game->player.nb_skins)
        game->player.vram_id = 0;
    init_sprite(game->player.vram_id, GAME2_PLAYER, game->sprites, game->vram);
    move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
}

static void move_everything(g2_state *game, uint8_t value)
{
    if (value > 2)
        game->bg_x++;
    else
        game->bg_x--;
    for (uint8_t i = 0; i < G2_NB_AMMUNITION; i++) {
        if (game->ammunitions[i].show == 0)
            continue;
        game->ammunitions[i].x += value;
    }
    for (uint8_t i = 0; i < G2_NB_ENEMY; i++) {
        if (game->enemies[i].show == 0)
            continue;
        game->enemies[i].x += value;
    }
    for (uint8_t i = 0; i < G2_NB_ENEMIES_AMMUNITION; i++) {
        if (game->enemies_ammunitions[i].show == 0)
            continue;
        game->enemies_ammunitions[i].x += value;
    }
    for (uint8_t i = 0; i < G2_NB_POWER_UP; i++) {
        if (game->power_up[i].show == 0)
            continue;
        game->power_up[i].x += value;
    }
}

static uint8_t handle_heart(g2_state *game, uint16_t clock, uint8_t i)
{
    if (game->player.hearts[i].show == 0) {
        if (game->sprites[GAME2_HEART1 + i].current
            != game->vram[GAME2_VRAM_HEART].end - 1 && (clock & 1) == 0)
            move_up_sprite(&game->sprites[GAME2_HEART1 + i], game->vram);
        if (game->sprites[GAME2_HEART1 + i].current
            == game->vram[GAME2_VRAM_HEART].end - 1)
            hide_sprite(&game->sprites[GAME2_HEART1 + i]);
        return 0;
    } else {
        if (game->sprites[GAME2_HEART1 + i].current
            != game->vram[GAME2_VRAM_HEART].start && (clock & 1) == 0) {
            move_sprite(GAME2_HEART1 + i,
                game->player.hearts[i].x, game->player.hearts[i].y);
            move_down_sprite(&game->sprites[GAME2_HEART1 + i], game->vram);
        }
        return 1;
    }
    return 0;
}

static void player_change_pos(g2_state *game, const input_state *input)
{
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
        move_everything(game, (uint8_t)-1);
    }
}

uint8_t g2_handle_player(g2_state *game,
    const input_state *input, uint16_t clock)
{
    uint8_t nb_heart = 0;

    if ((clock & 3) == 0)
        move_up_sprite(&game->sprites[GAME2_PLAYER], game->vram);
    player_change_pos(game, input);
    if (game->player.invincible > 0) {
        game->player.invincible--;
        if ((game->player.invincible & 3) == 0 && game->player.invincible != 0)
            move_sprite(GAME2_PLAYER, 0, 0);
        else
            move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
    }
    for (uint8_t i = 0; i < G2_NB_HEART; i++)
        nb_heart += handle_heart(game, clock, i);
    return nb_heart;
}

static uint8_t shoot(g2_state *game, uint8_t id, uint8_t launch)
{
    if (game->ammunitions[id].show == 1)
        return 0;
    game->ammunitions[id].show = 1;
    game->ammunitions[id].x = game->player.x;
    game->ammunitions[id].y = game->player.y;
    if (game->player.vram_id == GAME2_VRAM_SHIP2 && launch == 2)
        game->ammunitions[id].x -= 2;
    else if (game->player.vram_id == GAME2_VRAM_SHIP2 && launch == 1) {
        game->ammunitions[id].x += 3;
        game->ammunitions[id].y += 2;
    }
    sound_channel1(0x2A, 0x80, 0xF1, 0xA9, 0x87);
    return 1;
}

void g2_handle_ammunition(g2_state *game, uint8_t pressed)
{
    uint8_t launch = 1;
    uint8_t nb_ammunition = 3;

    if (game->player.vram_id == GAME2_VRAM_SHIP2) {
        launch = 2;
        nb_ammunition = G2_NB_AMMUNITION;
    }
    for (uint8_t i = 0; i < nb_ammunition; i++) {
        if ((pressed & J_A) && launch != 0)
            launch -= shoot(game, i, launch);
        if (game->ammunitions[i].show == 1) {
            game->ammunitions[i].y -= 2;
            move_sprite(GAME2_AMMUNITION1 + i,
                game->ammunitions[i].x, game->ammunitions[i].y);
            move_up_sprite(&game->sprites[GAME2_AMMUNITION1 + i], game->vram);
        }
        if (game->ammunitions[i].y <= 0)
            game->ammunitions[i].show = 0;
    }
}

void g2_handle_power_up(g2_state *game)
{
    for (uint8_t i = 0; i < G2_NB_POWER_UP; i++) {
        if (game->power_up[i].show == 0)
            continue;
        game->power_up[i].y++;
        move_sprite(GAME2_POWER_UP1 + i, game->power_up[i].x, game->power_up[i].y);
        if (game->power_up[i].y == 0)
            game->power_up[i].show = 0;
        if (game->power_up[i].x + 7 < game->player.x
            || game->power_up[i].x > game->player.x + 7)
            continue;
        if (game->power_up[i].y + 7 < game->player.y
            || game->power_up[i].y > game->player.y + 7)
            continue;
        if (game->sprites[GAME2_POWER_UP1 + i].current != game->vram[GAME2_VRAM_POWER_UP].start)
            g2_change_nb_live(game, 1);
        else
            change_ship(game);
        hide_sprite(&game->sprites[GAME2_POWER_UP1 + i]);
        game->power_up[i].show = 0;
    }
}