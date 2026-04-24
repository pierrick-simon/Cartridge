/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3
*/

#include <gb/gb.h>
#include "game3.h"
#include "input.h"

void game3Init(Game3State *game, sound_t *bgm)
{
    sound_start(bgm, 3, NULL, FALSE);
    game->score = 0;
}

// implement logik here
game_state_t game3Update(Game3State *game,
    const InputState *input, sound_t *bgm)
{
    (void)game;
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME3;
}
