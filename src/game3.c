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
#include "platformtile.h"

static void initPlatforms(Game3State *game)
{
    game->platforms[0].x = 80;
    game->platforms[0].y = 144;
    game->platforms[1].x = 56;
    game->platforms[1].y = 116;
    game->platforms[2].x = 104;
    game->platforms[2].y = 92;
    game->platforms[3].x = 40;
    game->platforms[3].y = 68;
    game->platforms[4].x = 120;
    game->platforms[4].y = 44;
    game->platforms[5].x = 72;
    game->platforms[5].y = 20;
}

static void drawPlatforms(const Game3State *game)
{
    uint8_t i = 0;
    uint8_t sid;

    while (i < G3_NB_PLATFORMS) {
        sid = G3_PLAT_SPR_OFF + i * 2;
        set_sprite_tile(sid, G3_PLAT_TILE_IDX);
        set_sprite_tile(sid + 1, G3_PLAT_TILE_IDX);
        move_sprite(sid, game->platforms[i].x, game->platforms[i].y);
        move_sprite(sid + 1, game->platforms[i].x + 8, game->platforms[i].y);
        i++;
    }
}

void game3Init(Game3State *game)
{
    game->score = 0;
    game->phase = G3_PLAY;
    game->rng = DIV_REG;
    game->px = 88;
    game->py = 128;
    game->vx = 0;
    game->vy = G3_JUMP_VY;
    initPlatforms(game);
    set_sprite_data(1, 7, player_tile);
    set_sprite_tile(G3_PLAYER_SPR, P_IDLE);
    move_sprite(G3_PLAYER_SPR, game->px, game->py);
    set_sprite_data(G3_PLAT_TILE_IDX, PLATFORM_TILE_SIZE, platform_tile);
    drawPlatforms(game);
    SHOW_BKG;
    SHOW_SPRITES;
}

game_state_t game3Update(Game3State *game,
    const InputState *input)
{
    (void)game;
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME3;
}
