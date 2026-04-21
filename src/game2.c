/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2
*/

#include <gb/gb.h>
#include "game2.h"
#include "input.h"

void game2Init(Game2State *game)
{
    game->score = 0;
}

// implement logik here
game_state_t game2Update(Game2State *game, const InputState *input)
{
    (void)game;
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}
