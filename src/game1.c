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
    game->player_x.w = 0;
    game->player_y.w = 0;
    game->player_x.b.h = 160 / 2;
    game->player_y.b.h = 144 / 2;
    game->player_flip = 0;

    HIDE_SPRITES;

    set_bkg_data(0,0,grass_tile);
    set_bkg_tiles(0,0,20,18,grass_map);
    
    set_sprite_data(1, 6, player_tile);
    set_sprite_tile(1, P_IDLE);
    move_sprite(1, game->player_x.b.h, game->player_y.b.h);

    SHOW_BKG;
    SHOW_SPRITES;
}

static void change_playertile(Game1State *game, const uint8_t touch)
{
    if ((touch & J_UP && touch & J_LEFT) || (touch & J_DOWN && touch & J_RIGHT)) {
        game->player_flip = S_FLIPY;
        return set_sprite_tile(1, P_DIAGO);
    }
    game->player_flip = 0;
    if ((touch & J_DOWN && touch & J_LEFT) || (touch & J_UP && touch & J_RIGHT))
        return set_sprite_tile(1, P_DIAGO);
    if (touch & (J_RIGHT | J_LEFT))
        return set_sprite_tile(1, P_RL);
    if (touch & (J_UP | J_DOWN))
        return set_sprite_tile(1, P_UD);
}

static void move_player(Game1State *game, const InputState *input)
{
    uint8_t touch = getHeld(input);
    uint16_t speed = SPEED;

    if (touch & (J_UP | J_DOWN) && touch & (J_LEFT | J_RIGHT))
        speed = DIAG_SPEED;
    if (touch & J_UP && game->player_y.b.h > 8 + 8)
        game->player_y.w -= speed;
    if (touch & J_DOWN && game->player_y.b.h < 144 + 8)
        game->player_y.w += speed;
    if (touch & J_RIGHT && game->player_x.b.h < 160)
        game->player_x.w += speed;
    if (touch & J_LEFT && game->player_x.b.h > 8)
        game->player_x.w -= speed;
    if (touch & (J_UP | J_DOWN | J_LEFT | J_RIGHT)) {
        move_sprite(1, game->player_x.b.h, game->player_y.b.h);
        change_playertile(game, touch);
        set_sprite_prop(1, game->player_flip);
    } else {
        set_sprite_tile(1, P_IDLE);
    }
}

// implement logik here
game_state_t game1Update(Game1State *game, const InputState *input)
{
    move_player(game, input);
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
