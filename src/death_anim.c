/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Generic death animation
*/

#include <gb/gb.h>
#include "input.h"
#include "death_anim.h"
#include "game_over_tile.h"

static const uint8_t s_black_row[21] = {
    240,240,240,240,240,240,240,240,240,240,
    240,240,240,240,240,240,240,240,240,240,
    240
};

// "GAME OVER" centred in 20 columns (black, GAME, space, OVER, black)

static const uint8_t s_gameover_row[21] = {
    240,240,240,240,240,240,240,
    241,242,243,244,
    240,
    245,246,244,247,
    240,240,240,240,240
};

static uint8_t s_da_timer;
static uint8_t s_da_closing;
static da_result_t s_da_result;

void death_anim_start(void)
{
    uint8_t i = 0;

    while (i < 40) {
        move_sprite(i, 0, 0);
        i++;
    }
    set_bkg_data(DA_TILE_BASE, GAME_OVER_NB_TILES, game_over_tiles);
    i = 0;
    while (i < 18) {
        set_win_tiles(0, i, 21, 1, s_black_row);
        i++;
    }
    set_win_tiles(0, DA_TEXT_ROW, 21, 1, s_gameover_row);
    move_win(0, 144);
    SHOW_WIN;
    s_da_timer = 0;
    s_da_closing = 0;
    s_da_result = DA_RUNNING;
}

static void clear_screen(void)
{
    uint8_t i = 0;

    while (i < 40) {
        move_sprite(i, 0, 0);
        i++;
    }
    move_bkg(0, 0);
    i = 0;
    while (i < 18) {
        set_bkg_tiles(0, i, 20, 1, s_black_row);
        i++;
    }
}

static da_result_t handle_closing(void)
{
    s_da_timer++;
    if (s_da_timer >= DA_CURTAIN_FRAMES) {
        set_win_tiles(0, DA_TEXT_ROW, 21, 1, s_black_row);
        move_win(0, 0);
        return s_da_result;
    }
    move_win(0, s_da_timer * DA_CURTAIN_STEP);
    return DA_RUNNING;
}

static void handle_opening(void)
{
    s_da_timer++;
    move_win(0, 144 - s_da_timer * DA_CURTAIN_STEP);
    SCY_REG += 2;
}

static void start_closing(da_result_t result)
{
    clear_screen();
    s_da_result = result;
    s_da_closing = 1;
    s_da_timer = 0;
}

static da_result_t handle_wait_input(const input_state *input)
{
    uint8_t pressed = get_just_pressed(input);

    if (pressed & J_A)
        start_closing(DA_RESTART);
    if (pressed & J_START)
        start_closing(DA_MENU);
    return DA_RUNNING;
}

da_result_t death_anim_update(const input_state *input)
{
    if (s_da_closing)
        return handle_closing();
    if (s_da_timer < DA_CURTAIN_FRAMES) {
        handle_opening();
        return DA_RUNNING;
    }
    return handle_wait_input(input);
}
