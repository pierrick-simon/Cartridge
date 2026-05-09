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

static void change_score(Game2State *game, uint8_t gain)
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

static void change_nb_live(Game2State *game, uint8_t gain)
{
    uint8_t last = 0;

    for (uint8_t i = 0; i < NB_HEART; i++) {
        if (gain == 0 && game->player.hearts[i].show == 1) {
            game->player.hearts[i].show = 0;
            break;
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
}

static void handle_heart(Game2State *game, uint8_t clock, uint8_t i)
{
    if (game->player.hearts[i].show == 0) {
        if (game->sprites[GAME2_HEART1 + i].current
            != game->vram[GAME2_VRAM_HEART].end - 1 && clock % 2)
            move_up_sprite(&game->sprites[GAME2_HEART1 + i], game->vram);
        if (game->sprites[GAME2_HEART1 + i].current
            == game->vram[GAME2_VRAM_HEART].end - 1)
            hide_sprite(&game->sprites[GAME2_HEART1 + i]);
    } else {
        if (game->sprites[GAME2_HEART1 + i].current
            != game->vram[GAME2_VRAM_HEART].start && clock % 2) {
            move_sprite(GAME2_HEART1 + i,
                game->player.hearts[i].x, game->player.hearts[i].y);
            move_down_sprite(&game->sprites[GAME2_HEART1 + i], game->vram);
        }
    }
}

void handle_player(Game2State *game, const InputState *input,
    uint8_t pressed, uint8_t clock)
{
    if (clock % 4 == 0)
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
            game->ammunitions[i].y--;
            move_sprite(GAME2_AMMUNITION1 + i,
                game->ammunitions[i].x, game->ammunitions[i].y);
            move_up_sprite(&game->sprites[GAME2_AMMUNITION1 + i], game->vram);
        }
        if (game->ammunitions[i].y <= 0)
            game->ammunitions[i].shoot = 0;
    }
}

static void handle_shown_enemy(Game2State *game, uint8_t i, uint8_t clock)
{
    if (clock % 4 == 0)
        move_up_sprite(&game->sprites[i + GAME2_ENEMY1], game->vram);
}

static void handle_explode_enemy(Game2State *game, uint8_t i, uint8_t clock)
{
    sprite_t *sprite = &game->sprites[i + GAME2_ENEMY1];
    uint8_t ship_skin = 0;

    if (sprite->current
        == game->vram[sprite->vram_id].end - 1) {
        game->enemies[i].explode = 0;
        game->enemies[i].show = 1;
        ship_skin = (rand() % NB_ENEMY_SKIN) + GAME2_VRAM_SHIP3;
        game->enemies[i].vram_id = ship_skin;
        init_sprite(ship_skin, GAME2_ENEMY1 + i, game->sprites, game->vram);
    } else if (clock % 2 == 0)
        move_up_sprite(sprite, game->vram);
}

static void check_hit_enemy(Game2State *game, enemy_t *enemy, uint8_t id)
{
    for (uint8_t i = 0; i < NB_AMMUNITION; i++) {
        if (game->ammunitions[i].shoot == 0)
            continue;
        if (game->ammunitions[i].x != 0
            && game->ammunitions[i].y == enemy->y + 8
            && game->ammunitions[i].x + 3 >= enemy->x + 1
            && game->ammunitions[i].x + 3 < enemy->x + 7) {
            enemy->explode = 1;
            init_sprite(GAME2_VRAM_EXPLOSION, GAME2_ENEMY1 + id,
                game->sprites, game->vram);
            game->ammunitions[i].y = 8;
            sound_channel4(0x00, 0xF2, 0x57, 0x80);
            change_score(game, 5);
            break;
        }
    }
}

void handle_enemies(Game2State *game, uint8_t clock)
{
    for (uint8_t i = 0; i < NB_ENEMY; i++) {
        if (game->enemies[i].show == 0)
            continue;
        if (game->enemies[i].explode == 0) {
            handle_shown_enemy(game, i, clock);
            check_hit_enemy(game, &game->enemies[i], i);
        } else
            handle_explode_enemy(game, i, clock);
        move_sprite(i + GAME2_ENEMY1, game->enemies[i].x, game->enemies[i].y);
    }
}