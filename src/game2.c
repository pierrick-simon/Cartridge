/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2
*/

#include <gb/gb.h>
#include "game2.h"
#include "input.h"

game_state_t game2Update(Game2State *game, const InputState *input)
{
    static uint8_t clock = 0;
    uint8_t pressed = getJustPressed(input);

    for (uint8_t i = 0; i < GAME2_NB_MUSIC; i++)
        sound_update(&game->musics[i]);
    handle_player(game, input, pressed, clock);
    handle_ammunition(game, pressed);
    handle_enemies(game, clock);
    move_bkg(game->bg_x, game->bg_y);
    game->bg_y--;
    clock++;
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}