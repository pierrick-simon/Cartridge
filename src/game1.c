/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 1
*/

#include <gb/gb.h>
#include "game1.h"
#include "grasstile.h"
#include "playertile.h"
#include "starwars.h"

void game1Init(Game1State *game, sound_t *bgm)
{
    sound_start(bgm, 3, NULL, FALSE);
    game->score = 0;
    game->player_x.w = 0;
    game->player_y.w = 0;
    game->player_x.b.h = 160 / 2;
    game->player_y.b.h = 144 / 2;
    game->player_flip = 0;
    game->dash_timer = 0;
    set_bkg_data(0, 0, grass_tile);
    set_bkg_tiles(0, 0, 20, 18, grass_map);
    set_sprite_data(1, 7, player_tile);
    set_sprite_tile(1, P_IDLE);
    move_sprite(1, game->player_x.b.h, game->player_y.b.h);
    SHOW_BKG;
    SHOW_SPRITES;
}

// implement logik here
game_state_t game1Update(Game1State *game,
    const InputState *input, sound_t *bgm)
{
    move_player(game, input);
    if (getJustPressed(input) & J_START)
        return STATE_MENU;
    return STATE_GAME1;
}
