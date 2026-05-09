/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_init
*/

#include <gb/gb.h>
#include "game1.h"
#include "grasstile.h"
#include "playertile.h"

static void init_value(Game1State *game)
{
    game->nb_vram = 0;
    game->score = 0;
}

static void init_background()
{
    set_bkg_data(0, 0, grass_tile);
    set_bkg_tiles(0, 0, 20, 18, grass_map);
}

static void init_vram(Game1State *game)
{
    init_vram_sprite(player_tile, P_NB_SPRITE,
        &game->nb_vram, game->vram);
}

static void init_player(Game1State *game)
{
    game->player.vram_id = GAME1_VRAM_PLAYER;
    game->player.nb_skins = 1;
    game->player.x.w = 0;
    game->player.y.w = 0;
    game->player.x.b.h = 160 / 2;
    game->player.y.b.h = 144 / 2;
    game->player.flip = 0;
    game->player.dash_timer = 0;
    init_sprite(game->player.vram_id, GAME1_PLAYER, game->sprites, game->vram);
    move_sprite(GAME1_PLAYER, game->player.x.b.h, game->player.y.b.h);
}

void game1Init(Game1State *game)
{
    init_value(game);
    init_background();
    init_vram(game);
    init_player(game);
    SHOW_BKG;
    SHOW_SPRITES;
}