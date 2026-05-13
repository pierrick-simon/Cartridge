/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3
*/

#include <gb/gb.h>
#include "game3.h"
#include "input.h"
#include "playertile.h"
#include "save_data.h"

game_state_t g3_update(g3_state *game, const input_state *input)
{
    if (game->phase == G3_DEAD)
        return updateDead(game, input);
    return updatePlay(game, input);
}
