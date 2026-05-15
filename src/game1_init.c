/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_init
*/

#include <gb/gb.h>
#include <rand.h>
#include "game1.h"
#include "moontile.h"
#include "playertile.h"
#include "hearttile.h"
#include "flash.h"
#include "number.h"
#include "asteroid.h"
#include "star.h"
#include "explosion.h"

static void init_asteroid(g1_state *game, uint8_t i)
{
    init_sprite(GAME1_VRAM_ASTEROID, GAME1_F_ASTEROID + i,
        game->sprites, game->vram);
    game->asteroid[i].x = 0;
    game->asteroid[i].y = 0;
    game->asteroid[i].timer = 0;
}

static void init_attacks(g1_state *game)
{
    for (uint8_t i = 0; i < G1_NB_ASTEROID; ++i)
        init_asteroid(game, i);
    init_sprite(GAME1_VRAM_STAR, GAME1_STAR,
        game->sprites, game->vram);
    game->star.x.w = 0;
    game->star.y.w = 0;
    game->star.timer = 0;
    game->star.here = 0;
}


static void init_value(g1_state *game)
{
    initarand(sys_time);
    game->nb_vram = 0;
    game->score = 0;
    game->clock = 0;
    game->spawn_timer = G1_ATTACK_COOLDOWN;
    game->max_asteroid = G1_MIN_ASTEROID;
}

static void init_background()
{
    set_bkg_data(0, 0, moon_tile);
    set_bkg_tiles(0, 0, 20, 18, moon_map);
}

static void init_vram(g1_state *game)
{
    init_vram_sprite(player_tile, P_NB_SPRITE,
        &game->nb_vram, game->vram);
    init_vram_sprite(heart_tiles, HEART_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(flash_tile, NB_FLASH,
        &game->nb_vram, game->vram);
    init_vram_sprite(number_tiles, NUMBER_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(asteroid_tile, NB_ASTEROID,
        &game->nb_vram, game->vram);
    init_vram_sprite(star_tile, 1,
        &game->nb_vram, game->vram);
    init_vram_sprite(explosion_tiles, EXPLOSION_SIZE,
        &game->nb_vram, game->vram);
}

static void init_score(g1_state *game)
{
    for (uint8_t i = 0; i < G1_NB_SCORE; i++) {
        init_sprite(GAME1_VRAM_SCORE, GAME1_F_SCORE + i,
            game->sprites, game->vram);
        move_sprite(GAME1_F_SCORE + i, 8 + 6 * i, 148);
    }
}

static void init_hearts(g1_state *game)
{
    for (uint8_t i = 0; i < G1_NB_HEART; i++) {
        init_sprite(GAME1_VRAM_HEART, GAME1_F_HEART + i,
            game->sprites, game->vram);
        game->player.hearts[i].show = 1;
        game->player.hearts[i].y = 148;
        game->player.hearts[i].x = 164 - 10 * G1_NB_HEART + 10 * i;
        move_sprite(GAME1_F_HEART + i,
            game->player.hearts[i].x, game->player.hearts[i].y);
    }
}

static void init_player(g1_state *game)
{
    game->player.nb_skins = 1;
    game->player.x.w = 0;
    game->player.y.w = 0;
    game->player.x.b.h = 160 / 2;
    game->player.y.b.h = 144 / 2;
    game->player.flip = 0;
    game->player.dash_timer = 0;
    game->player.cd_timer = 0;
    init_sprite(GAME1_VRAM_PLAYER, GAME1_PLAYER, game->sprites, game->vram);
    move_sprite(GAME1_PLAYER, game->player.x.b.h, game->player.y.b.h);
    init_hearts(game);
    init_score(game);
    init_sprite(GAME1_VRAM_FLASH, GAME1_FLASH, game->sprites, game->vram);
    move_sprite(GAME1_FLASH, 160 / 2, 148);
}

void g1_init(g1_state *game)
{
    init_value(game);
    init_background();
    init_vram(game);
    init_player(game);
    init_attacks(game);
    SHOW_BKG;
    SHOW_SPRITES;
}