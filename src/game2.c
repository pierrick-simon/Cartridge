/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2
*/

#include <gb/gb.h>
#include "game2.h"
#include "input.h"

game_state_t g2_update(g2_state *game, const input_state *input)
{
    static uint8_t clock = 0;
    uint8_t pressed = getJustPressed(input);

    for (uint8_t i = 0; i < GAME2_NB_MUSIC; i++)
        sound_update(&game->musics[i]);
    g2_handle_player(game, input, pressed, clock);
    g2_handle_ammunition(game, pressed);
    g2_handle_enemies(game, clock);
    move_bkg(game->bg_x, game->bg_y);
    game->bg_y--;
    clock++;
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}