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
    sound_start(&game->musics[GAME2_THEME], 3, game2_theme_music, TRUE, 0x80);
    game->nb_sprites = 0;
    set_bkg_data(0, 0, space_tiles);
    set_bkg_tiles(0, 0, 20, 18, space_map);
    init_sprite(spaceship1_tiles, SPACESHIP1_SIZE, &game->nb_sprites, game->sprites);
    init_sprite(spaceship2_tiles, SPACESHIP2_SIZE, &game->nb_sprites, game->sprites);
    game->player.sprite_id = 0;
    game->player.nb_sprite = 2;
    game->player.y = 160 / 2;
    game->player.x = 144 / 2;
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

    sound_update(&game->musics[GAME2_THEME]);
    if (clock == 4) {
        move_up_sprite(&game->sprites[game->player.sprite_id]);
        clock = 0;
    }
    clock++;
    change_ship(game, pressed);  
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}
