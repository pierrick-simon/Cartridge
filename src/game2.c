/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2
*/

#include <gb/gb.h>
#include "game2.h"
#include "input.h"
#include "save_data.h"
#include "death_anim.h"

static game_state_t g2_updatePlay(g2_state *game,
    const input_state *input)
{
    static uint16_t clock = 0;
    uint8_t pressed = get_just_pressed(input);
    uint8_t nb_live = 0;

    for (uint8_t i = 0; i < GAME2_NB_MUSIC; i++)
        sound_update(&game->musics[i]);
    nb_live = g2_handle_player(game, input, clock);
    g2_handle_ammunition(game, pressed);
    g2_handle_enemies_ammunition(game);
    g2_handle_enemies(game, clock);
    g2_handle_power_up(game);
    move_bkg(game->bg_x, game->bg_y);
    game->bg_y--;
    clock++;
    if (pressed & J_START)
        return STATE_MENU;
    if (nb_live == 0) {
        save_score(game->score, 1);
        game->phase = G2_DEAD;
        death_anim_start();
    }
    return STATE_GAME2;
}

static game_state_t g2_updateDead(g2_state *game, const input_state *input)
{
    da_result_t r;

    for (uint8_t i = 0; i < GAME2_NB_MUSIC; i++)
        sound_update(&game->musics[i]);
    r = death_anim_update(input);
    if (r == DA_RESTART) {
        g2_init(game);
        HIDE_WIN;
        return STATE_GAME2;
    }
    if (r == DA_MENU)
        return STATE_MENU;
    return STATE_GAME2;
}

game_state_t g2_update(g2_state *game, const input_state *input)
{
    if (game->phase == G2_DEAD)
        return g2_updateDead(game, input);
    return g2_updatePlay(game, input);
}