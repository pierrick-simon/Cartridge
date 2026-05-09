/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_handle
*/

#include <gb/gb.h>
#include "game1.h"

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

void g1_handle_player(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock)
{
    change_nb_live(game, clock % 4);
    for (uint8_t i = 0; i < G1_NB_HEART; i++)
        handle_heart(game, clock, i);
    g1_move_player(game, input);
}
