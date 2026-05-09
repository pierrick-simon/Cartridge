/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include "game1.h"

// implement logik here
game_state_t g1_update(g1_state *game,
    const input_state *input)
{
    static uint8_t clock = 0;

    g1_handle_player(game, input, getJustPressed(input), clock);
    clock++;
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
