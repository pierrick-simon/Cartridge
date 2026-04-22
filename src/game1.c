/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include <stdio.h>
#include "game1.h"
#include "input.h"
#include "grasstile.h"
#include "playertile.h"

void game1Init(Game1State *game)
{
    game->score = 0;
    game->player_x = 160 / 2;
    game->player_y = 144 / 2;

    set_bkg_data(0,0,grass_tile);
    set_bkg_tiles(0,0,20,18,grass_map);
    
    set_sprite_data(1, 3, player_tile);
    set_sprite_tile(1, FRONT);
    move_sprite(1, game->player_x, game->player_y);

    SHOW_BKG;
    SHOW_SPRITES;
}

void move_player(Game1State *game, const InputState *input)
{
    uint8_t touch = getHeld(input);
    uint8_t change = 0;

    if (touch & J_UP && game->player_y > 8 + 8) {
        game->player_y -= 2;
        change = 1;
        set_sprite_tile(1, FRONT);
    }
    if (touch & J_DOWN && game->player_y < 144 + 8) {
        game->player_y += 2;
        change = 1;
        set_sprite_tile(1, FRONT);
    }
    if (touch & J_RIGHT && game->player_x < 160) {
        game->player_x += 2;
        change = 1;
        set_sprite_tile(1, RIGHT);
    }
    if (touch & J_LEFT && game->player_x > 8) {
        game->player_x -= 2;
        change = 1;
        set_sprite_tile(1, LEFT);
    }
    if (change == 1)
        move_sprite(1, game->player_x, game->player_y);
}

// implement logik here
game_state_t game1Update(Game1State *game, const InputState *input)
{
    move_player(game, input);
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
