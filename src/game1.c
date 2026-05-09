/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include "game1.h"

// implement logik here
game_state_t game1Update(Game1State *game,
    const InputState *input)
{
    move_player(game, input);
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
