/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include "game1.h"

static void handle_clock(g1_state *game, uint8_t *clock)
{
    if (game->player.cd_timer != 0)
        --game->player.cd_timer;
    if (game->player.dash_timer != 0)
        --game->player.dash_timer;
    ++(*clock);
}

game_state_t g1_update(g1_state *game,
    const input_state *input)
{
    static uint8_t clock = 0;

    g1_handle_player(game, input, get_just_pressed(input), clock);
    g1_handle_attacks(game, input, get_just_pressed(input), clock);
    if (clock % 60 == 0)
        g1_change_score(game, 1);
    handle_clock(game, &clock);
    if (get_just_pressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
