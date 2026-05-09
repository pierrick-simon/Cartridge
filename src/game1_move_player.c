/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** move_player
*/

#include <stdio.h>
#include <string.h>
#include <gb/gb.h>
#include "game1.h"
#include "playertile.h"
#include "input.h"

static void change_playertile(g1_state *game, const input_state *input)
{
    uint8_t touch = getHeld(input);
    uint8_t dash = game->player.dash_timer >= G1_DASH_DELTA_TIME;

    if ((touch & J_UP && touch & J_LEFT) || (touch & J_DOWN && touch & J_RIGHT)) {
        game->player.flip = S_FLIPY;
        return move_to_tile(&game->sprites[GAME1_PLAYER], game->vram, (dash) ? P_DIAGO_F: P_DIAGO);
    }
    game->player.flip = 0;
    if ((touch & J_DOWN && touch & J_LEFT) || (touch & J_UP && touch & J_RIGHT))
        return move_to_tile(&game->sprites[GAME1_PLAYER], game->vram, (dash) ? P_DIAGO_F: P_DIAGO);
    if (touch & (J_RIGHT | J_LEFT))
        return move_to_tile(&game->sprites[GAME1_PLAYER], game->vram, (dash) ? P_RL_F: P_RL);
    if (touch & (J_UP | J_DOWN))
        return move_to_tile(&game->sprites[GAME1_PLAYER], game->vram, (dash) ? P_UD_F: P_UD);
}

static void replace_player(g1_state *game)
{
    if (game->player.y.b.h < 8 + 8)
        game->player.y.w = G1_H_TO_W(8 + 8);
    if (game->player.y.b.h > 144 - 8)
        game->player.y.w = G1_H_TO_W(144 - 8);
    if (game->player.x.b.h > 160)
        game->player.x.w = G1_H_TO_W(160);
    if (game->player.x.b.h < 8)
        game->player.x.w = G1_H_TO_W(8);
}

static void move_classic(g1_state *game,
    const uint8_t touch, const uint16_t speed)
{
    if (touch & J_UP)
        game->player.y.w -= speed;
    if (touch & J_DOWN)
        game->player.y.w += speed;
    if (touch & J_RIGHT)
        game->player.x.w += speed;
    if (touch & J_LEFT)
        game->player.x.w -= speed;
}

static void move_dash(g1_state *game,
    const uint8_t touch, const uint16_t speed)
{
    if (game->player.dash_timer != 0) {
        if (game->player.dash_timer >= G1_DASH_DELTA_TIME)
            return move_classic(game, touch, speed * G1_DASH_MULTI);
        return move_classic(game, touch, speed);
    }
    game->player.dash_timer = G1_DASH_COOLDOWN;
    move_classic(game, touch, speed * G1_DASH_MULTI);
}

void g1_move_player(g1_state *game, const input_state *input)
{
    uint8_t touch = getHeld(input);
    uint16_t speed = G1_SPEED;

    if (touch & (J_UP | J_DOWN) && touch & (J_LEFT | J_RIGHT))
        speed = G1_DIAG_SPEED;
    if (input->justPressed & J_A || game->player.dash_timer >= G1_DASH_DELTA_TIME)
        move_dash(game, touch, speed);
    else
        move_classic(game, touch, speed);
    if (touch & (J_UP | J_DOWN | J_LEFT | J_RIGHT)) {
        replace_player(game);
        move_sprite(GAME1_PLAYER, game->player.x.b.h, game->player.y.b.h);
        change_playertile(game, input);
        set_sprite_prop(GAME1_PLAYER, game->player.flip);
    } else
        move_to_tile(&game->sprites[GAME1_PLAYER], game->vram, P_IDLE);
    if (game->player.dash_timer != 0)
        --game->player.dash_timer;
}