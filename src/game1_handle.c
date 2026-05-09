/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_handle
*/

#include <gb/gb.h>
#include "game1.h"
#include "flash.h"

void g1_change_score(g1_state *game, uint8_t gain)
{
    uint16_t score;

    game->score += gain;
    score = game->score;
    move_to_tile(&game->sprites[GAME1_SCORE5], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME1_SCORE4], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME1_SCORE3], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME1_SCORE2], game->vram, score % 10);
    score /= 10;
    move_to_tile(&game->sprites[GAME1_SCORE1], game->vram, score % 10);
}

static void handle_heart(g1_state *game, uint8_t clock, uint8_t i)
{
    if (game->player.hearts[i].show == 0) {
        if (game->sprites[GAME1_HEART1 + i].current
            != game->vram[GAME1_VRAM_HEART].end - 1 && clock % 2)
            move_up_sprite(&game->sprites[GAME1_HEART1 + i], game->vram);
        if (game->sprites[GAME1_HEART1 + i].current
            == game->vram[GAME1_VRAM_HEART].end - 1)
            hide_sprite(&game->sprites[GAME1_HEART1 + i]);
    } else {
        if (game->sprites[GAME1_HEART1 + i].current
            != game->vram[GAME1_VRAM_HEART].start && clock % 2) {
            move_sprite(GAME1_HEART1 + i,
                game->player.hearts[i].x, game->player.hearts[i].y);
            move_down_sprite(&game->sprites[GAME1_HEART1 + i], game->vram);
        }
    }
}

static void change_nb_live(g1_state *game, uint8_t gain)
{
    uint8_t last = 0;

    for (uint8_t i = 0; i < G1_NB_HEART; i++) {
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

static void handle_flash(g1_state *game)
{
    if (game->player.dash_timer == 0 || (game->player.dash_timer / 20) % 2 == 0)
        return move_to_tile(&game->sprites[GAME1_FLASH], game->vram, FULL);
    else 
        return move_to_tile(&game->sprites[GAME1_FLASH], game->vram, EMPTY);
}

void g1_handle_player(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock)
{
    g1_move_player(game, input);
    handle_flash(game);
    change_nb_live(game, clock % 4);
    for (uint8_t i = 0; i < G1_NB_HEART; i++)
        handle_heart(game, clock, i);
}
