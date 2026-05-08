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
    game->nb_sprites = 0;
    game->bg_x = 0;
    game->bg_y = 0;
    sound_start(&game->musics[GAME2_THEME], 3, game2_theme_music, TRUE, 0x80);
    set_bkg_data(0, 4, space_tiles);
    set_bkg_tiles(0, 0, 32, 32, space_map);
    init_sprite(spaceship1_tiles, SPACESHIP1_SIZE, &game->nb_sprites, game->sprites);
    init_sprite(spaceship2_tiles, SPACESHIP2_SIZE, &game->nb_sprites, game->sprites);
    init_sprite(projectile1_tiles, PROJECTILE1_SIZE, &game->nb_sprites, game->sprites);
    copy_sprite(&game->nb_sprites, 2, game->sprites);
    copy_sprite(&game->nb_sprites, 2, game->sprites);
    game->player.sprite_id = 0;
    game->player.nb_sprite = 2;
    game->player.y = 144 - 8;
    game->player.x = 160 / 2;
    move_sprite(game->player.sprite_id + 1, game->player.x, game->player.y);
    SHOW_BKG;
    SHOW_SPRITES;
}

static void change_ship(Game2State *game, uint8_t pressed)
{
    if (!(pressed & J_A))
        return;
    game->player.sprite_id++;
    if (game->player.sprite_id == game->player.nb_sprite)
        game->player.sprite_id = 0;
    for (uint8_t i = 0; i < game->player.nb_sprite; i++) {
        if (i == game->player.sprite_id)
            move_sprite(i + 1, game->player.x, game->player.y);
        else
            hide_sprite(&game->sprites[i]);
    }
}

game_state_t game2Update(Game2State *game,
    const InputState *input)
{
    static uint8_t clock = 0;
    uint8_t pressed = getJustPressed(input);
    static uint8_t projectile_y = 0;
    static uint8_t projectile_x = 0;

    if (projectile_y) {
        projectile_y--;
        move_sprite(3, projectile_x, projectile_y);
        move_up_sprite(&game->sprites[2]);
    }
    sound_update(&game->musics[GAME2_THEME]);
    if (clock == 4) {
        move_up_sprite(&game->sprites[game->player.sprite_id]);
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
        move_sprite(game->player.sprite_id + 1, game->player.x, game->player.y);
    }
    if (getHeld(input) & J_RIGHT) {
        game->bg_x++;
        game->player.x++;
        if (game->player.x > 160 - 8) {
            game->player.x = 160 - 8;
            game->bg_x++;
        }
        move_bkg(game->bg_x, game->bg_y);
        move_sprite(game->player.sprite_id + 1, game->player.x, game->player.y);
    }
    if (pressed & J_UP) {
        projectile_y = game->player.y;
        projectile_x = game->player.x;
    }
    // if (getHeld(input) & J_UP) {
    //     game->bg_y--;
    //     move_bkg(game->bg_x, game->bg_y);
    // }
    // if (getHeld(input) & J_DOWN) {
    //     game->bg_y++;
    //     move_bkg(game->bg_x, game->bg_y);
    // }
    game->bg_y--;
    move_bkg(game->bg_x, game->bg_y);
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}
