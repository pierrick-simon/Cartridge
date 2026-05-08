/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2
*/

#include <gb/gb.h>
#include "game2.h"
#include "input.h"
#include "spacetile.h"
#include "spaceship1.h"
#include "spaceship2.h"
#include "game2_theme.h"

void game2Init(Game2State *game)
{
    game->nb_vram = 0;
    game->bg_x = 0;
    game->bg_y = 0;
    sound_start(&game->musics[GAME2_THEME], 3, game2_theme_music, TRUE, 0x80);
    init_vram_sprite(spaceship1_tiles, SPACESHIP1_SIZE, &game->nb_vram, game->vram);
    init_vram_sprite(spaceship2_tiles, SPACESHIP2_SIZE, &game->nb_vram, game->vram);
    init_vram_sprite(projectile1_tiles, PROJECTILE1_SIZE, &game->nb_vram, game->vram);
    game->player.vram_id = GAME2_SHIP1;
    game->player.nb_skins = 2;
    game->player.x = 160 / 2;
    game->player.y = 144 - 8;
    init_sprite(game->player.vram_id, 0, game->sprites, game->vram);
    move_sprite(game->sprites[0].id, game->player.x, game->player.y);
    set_bkg_data(0, 4, space_tiles);
    set_bkg_tiles(0, 0, 32, 32, space_map);
    SHOW_BKG;
    SHOW_SPRITES;
}

static void change_ship(Game2State *game, uint8_t pressed)
{
    if (!(pressed & J_A))
        return;
    game->player.vram_id++;
    if (game->player.vram_id >= game->player.nb_skins)
        game->player.vram_id = 0;
    init_sprite(game->player.vram_id, 0, game->sprites, game->vram);
    move_sprite(game->sprites[0].id, game->player.x, game->player.y);
}

game_state_t game2Update(Game2State *game, const InputState *input)
{
    static uint8_t clock = 0;
    uint8_t pressed = getJustPressed(input);

    sound_update(&game->musics[GAME2_THEME]);
    if (clock == 4) {
        move_up_sprite(&game->sprites[0], game->vram);
        clock = 0;
    }
    clock++;
    change_ship(game, pressed);
    if (getHeld(input) & J_LEFT) {
        game->bg_x--;
        game->player.x--;
        if (game->player.x < 16) {
            game->player.x = 16;
            game->bg_x--;
        }
        move_bkg(game->bg_x, game->bg_y);
        move_sprite(game->sprites[0].id, game->player.x, game->player.y);
    }
    if (getHeld(input) & J_RIGHT) {
        game->bg_x++;
        game->player.x++;
        if (game->player.x > 160 - 8) {
            game->player.x = 160 - 8;
            game->bg_x++;
        }
        move_bkg(game->bg_x, game->bg_y);
        move_sprite(game->sprites[0].id, game->player.x, game->player.y);
    }
    game->bg_y--;
    move_bkg(game->bg_x, game->bg_y);
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}