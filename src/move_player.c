/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** move_player
*/

#include <stdio.h>
#include <gb/gb.h>
#include <string.h>
#include "game1.h"
#include "playertile.h"
#include "input.h"

static void change_playertile(Game1State *game, const InputState *input)
{
    uint8_t touch = getHeld(input);
    uint8_t dash = (input->current & J_A) || game->dash_timer >= DASH_DELTA_TIME;

    if ((touch & J_UP && touch & J_LEFT) || (touch & J_DOWN && touch & J_RIGHT)) {
        game->player_flip = S_FLIPY;
        return set_sprite_tile(1, (dash) ? P_DIAGO_F: P_DIAGO);
    }
    game->player_flip = 0;
    if ((touch & J_DOWN && touch & J_LEFT) || (touch & J_UP && touch & J_RIGHT))
        return set_sprite_tile(1, (dash) ? P_DIAGO_F: P_DIAGO);
    if (touch & (J_RIGHT | J_LEFT))
        return set_sprite_tile(1, (dash) ? P_RL_F: P_RL);
    if (touch & (J_UP | J_DOWN))
        return set_sprite_tile(1, (dash) ? P_UD_F: P_UD);
}

static void replace_player(Game1State *game)
{
    if (game->player_y.b.h < 8 + 8)
        game->player_y.w = H_TO_W(8 + 8);
    if (game->player_y.b.h > 144 + 8)
        game->player_y.w = H_TO_W(144 + 8);
    if (game->player_x.b.h > 160)
        game->player_x.w = H_TO_W(160);
    if (game->player_x.b.h < 8)
        game->player_x.w = H_TO_W(8);
}

static void move_classic(Game1State *game,
    const uint8_t touch, const uint16_t speed)
{
    if (touch & J_UP)
        game->player_y.w -= speed;
    if (touch & J_DOWN)
        game->player_y.w += speed;
    if (touch & J_RIGHT)
        game->player_x.w += speed;
    if (touch & J_LEFT)
        game->player_x.w -= speed;
}

static void move_dash(Game1State *game,
    const uint8_t touch, const uint16_t speed)
{
    if (game->dash_timer != 0) {
        if (game->dash_timer >= DASH_DELTA_TIME)
            return move_classic(game, touch, speed * DASH_MULTI);
        return move_classic(game, touch, speed);
    }
    game->dash_timer = DASH_COOLDOWN;
    move_classic(game, touch, speed * DASH_MULTI);
}

void move_player(Game1State *game, const InputState *input)
{
    uint8_t touch = getHeld(input);
    uint16_t speed = SPEED;

    if (touch & (J_UP | J_DOWN) && touch & (J_LEFT | J_RIGHT))
        speed = DIAG_SPEED;
    if (input->justPressed & J_A || game->dash_timer >= DASH_DELTA_TIME)
        move_dash(game, touch, speed);
    else
        move_classic(game, touch, speed);
    if (touch & (J_UP | J_DOWN | J_LEFT | J_RIGHT)) {
        replace_player(game);
        move_sprite(1, game->player_x.b.h, game->player_y.b.h);
        change_playertile(game, input);
        set_sprite_prop(1, game->player_flip);
    } else
        set_sprite_tile(1, P_IDLE);
    if (game->dash_timer != 0)
        --game->dash_timer;
}