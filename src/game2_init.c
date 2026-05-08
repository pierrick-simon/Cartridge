/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** game2_init
*/

#include <gb/gb.h>
#include <rand.h>
#include "game2.h"
#include "spacetile.h"
#include "spaceship1.h"
#include "spaceship2.h"
#include "spaceship3.h"
#include "spaceship4.h"
#include "game2_theme.h"
#include "explosion.h"
#include "power.h"

static void init_player(Game2State *game)
{
    game->player.vram_id = GAME2_VRAM_SHIP1;
    game->player.nb_skins = NB_SKIN;
    game->player.x = 160 / 2;
    game->player.y = 144 - 8;
    init_sprite(game->player.vram_id, GAME2_PLAYER, game->sprites, game->vram);
}

static void init_ammunition(Game2State *game)
{
    for (uint8_t i = 0; i <  NB_AMMUNITION; i++) {
        game->ammunitions[i].shoot = 0;
        game->ammunitions[i].x = 0;
        game->ammunitions[i].y = 0;
        init_sprite(GAME2_VRAM_AMMUNITION, i + GAME2_AMMUNITION1,
            game->sprites, game->vram);
        hide_sprite(&game->sprites[i]);
    }
}

static void init_vram(Game2State *game)
{
    init_vram_sprite(spaceship1_tiles, SPACESHIP1_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(spaceship2_tiles, SPACESHIP2_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(spaceship3_tiles, SPACESHIP3_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(spaceship4_tiles, SPACESHIP4_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(projectile1_tiles, PROJECTILE1_SIZE,
        &game->nb_vram, game->vram);
    init_vram_sprite(explosion_tiles, EXPLOSION_SIZE,
        &game->nb_vram, game->vram);
}

static void init_enemies(Game2State *game)
{
    uint8_t ship_skin = 0;

    for (uint8_t i = 0; i < NB_ENEMY; i++) {
        ship_skin = (rand() % NB_ENEMY_SKIN) + GAME2_VRAM_SHIP3;
        init_sprite(ship_skin, GAME2_ENEMY1 + i,
            game->sprites, game->vram);
        game->sprites[GAME2_ENEMY1 + i].current = rand() % SPACESHIP3_SIZE
            + game->vram[ship_skin].start;
        game->enemies[i].vram_id = ship_skin;
        game->enemies[i].show = 1;
        game->enemies[i].x = 16 + i * 8;
        game->enemies[i].y = 16 + i * 4;
        game->enemies[i].explode = 0;
    }
}

void game2Init(Game2State *game)
{
    game->nb_vram = 0;
    game->bg_x = 0;
    game->bg_y = 0;
    sound_start(&game->musics[GAME2_THEME], 3, game2_theme_music, TRUE, 0x80);
    sound_start(&game->musics[GAME2_POWER_UP], 1, power_up_sound, FALSE, 0x80);
    sound_start(&game->musics[GAME2_POWER_DOWN], 1, power_down_sound, FALSE, 0x80);
    game->musics[GAME2_POWER_UP].state = SND_OFF;
    game->musics[GAME2_POWER_DOWN].state = SND_OFF;
    set_bkg_data(0, 4, space_tiles);
    set_bkg_tiles(0, 0, 32, 32, space_map);
    init_vram(game);
    init_player(game);
    init_ammunition(game);
    init_enemies(game);
    move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
    SHOW_BKG;
    SHOW_SPRITES;
}