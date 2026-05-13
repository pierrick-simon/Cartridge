/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 3 platforms, scroll, difficulty
*/

#include <gb/gb.h>
#include "game3.h"

static uint8_t nextRng(uint8_t rng)
{
    return rng * 53 + 1;
}

static uint8_t getGapMin(uint16_t score)
{
    uint8_t extra = (uint8_t)(score / G3_DIFF_STEP);

    if (extra > G3_DIFF_MAX_EXTRA)
        extra = G3_DIFF_MAX_EXTRA;
    return G3_PLAT_GAP_MIN + extra;
}

void g3_recyclePlatform(g3_state *game, uint8_t i, uint8_t topy)
{
    uint8_t gap_min = getGapMin(game->score);
    uint8_t gap_range = G3_PLAT_GAP_MAX - gap_min;

    game->rng = nextRng(game->rng);
    game->platforms[i].x =
        8 + (game->rng % (G3_SCREEN_W - G3_PLAT_W - 16));
    game->rng = nextRng(game->rng);
    game->platforms[i].y = topy - gap_min
        - (game->rng % gap_range);
    game->platforms[i].vx = 0;
    if (game->score >= G3_MOBILE_SCORE && (game->rng % 3) == 0) {
        game->rng = nextRng(game->rng);
        game->platforms[i].vx =
            (game->rng % 2) ? G3_PLAT_SPEED : -G3_PLAT_SPEED;
    }
}

void g3_scrollWorld(g3_state *game, uint8_t delta)
{
    uint8_t i = 0;
    uint8_t sid;
    uint8_t top_y = 255;

    game->score += delta;
    while (i < G3_NB_PLATFORMS) {
        game->platforms[i].y += delta;
        if (game->platforms[i].y < top_y)
            top_y = game->platforms[i].y;
        i++;
    }
    i = 0;
    while (i < G3_NB_PLATFORMS) {
        if (game->platforms[i].y > G3_SCREEN_H + 16) {
            g3_recyclePlatform(game, i, top_y);
            top_y = game->platforms[i].y;
        }
        sid = G3_PLAT_SPR_OFF + i * 2;
        move_sprite(sid, game->platforms[i].x, game->platforms[i].y);
        move_sprite(sid + 1, game->platforms[i].x + 8, game->platforms[i].y);
        i++;
    }
}

static void movePlatform(g3_state *game, uint8_t i)
{
    uint8_t sid = G3_PLAT_SPR_OFF + i * 2;

    game->platforms[i].x += game->platforms[i].vx;
    if (game->platforms[i].x <= 8
        || game->platforms[i].x >= G3_SCREEN_W - G3_PLAT_W - 8)
        game->platforms[i].vx = -game->platforms[i].vx;
    move_sprite(sid, game->platforms[i].x, game->platforms[i].y);
    move_sprite(sid + 1, game->platforms[i].x + 8, game->platforms[i].y);
}

void g3_movePlatforms(g3_state *game)
{
    uint8_t i = 0;

    while (i < G3_NB_PLATFORMS) {
        if (game->platforms[i].vx != 0)
            movePlatform(game, i);
        i++;
    }
}
