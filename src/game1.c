/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include "game1.h"
#include "save_data.h"

static void handle_clock(g1_state *game)
{
    if (game->player.cd_timer != 0)
        --game->player.cd_timer;
    if (game->player.dash_timer != 0)
        --game->player.dash_timer;
    ++(game->clock);
}

game_state_t g1_update(g1_state *game,
    const input_state *input)
{
    g1_handle_player(game, input, get_just_pressed(input));
    g1_handle_attacks(game, input, get_just_pressed(input));
    if (game->clock % 60 == 0)
        g1_change_score(game, 1);
    handle_clock(game);
    if (get_just_pressed(input) & J_START || game->player.hearts[G1_NB_HEART - 1].show == 0) {
        save_score(game->score, 0);
        return STATE_MENU;
    }
    return STATE_GAME1;
}
