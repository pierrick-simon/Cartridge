/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include "game1.h"
#include "input.h"

void game1Init(Game1State *game)
{
    game->score = 0;
}

// implement logik here
game_state_t game1Update(Game1State *game, const InputState *input)
{
    (void)game;
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
