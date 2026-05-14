#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "menu.h"
#include "input.h"
#include "cursor.h"
#include "number.h"
#include "starwars.h"
#include "save_data.h"
#include "menutile.h"

static void m_init_sprite(menu_state *menu)
{
    menu->cursor = 0;
    init_sprite(MENU_VRAM_CURSOR, MENU_CURSOR, menu->sprites, menu->vram);
    move_sprite(MENU_CURSOR, 28, 56 + 16 * menu->cursor);
    for (uint8_t i = 0; i < M_NB_NUMBER; i++) {
        init_sprite(MENU_VRAM_NUMBER, MENU_SCORE1 + i,
            menu->sprites, menu->vram);
        move_sprite(MENU_SCORE1 + i, 71 + 6 * i, 112);
    }
    set_bkg_data(0, 0, menu_tile);
    set_bkg_tiles(0, 0, 20, 18, menu_map);
}

static void change_score(menu_state *menu, uint16_t score)
{
    move_to_tile(&menu->sprites[MENU_SCORE5], menu->vram, score % 10);
    score /= 10;
    move_to_tile(&menu->sprites[MENU_SCORE4], menu->vram, score % 10);
    score /= 10;
    move_to_tile(&menu->sprites[MENU_SCORE3], menu->vram, score % 10);
    score /= 10;
    move_to_tile(&menu->sprites[MENU_SCORE2], menu->vram, score % 10);
    score /= 10;
    move_to_tile(&menu->sprites[MENU_SCORE1], menu->vram, score % 10);
}

void m_init(menu_state *menu)
{
    menu->nb_vram = 0;
    sound_start(&menu->musics[MENU_THEME], 3, starwars_music, TRUE, 0xFF);
    init_vram_sprite(CursorTiles, NB_CURSOR_TILE, &menu->nb_vram, menu->vram);
    init_vram_sprite(number_tiles, NUMBER_SIZE, &menu->nb_vram, menu->vram);
    printf(" ");
    m_init_sprite(menu);
    menu->cursor = 0;
    if (has_existing_save())
        load_save(menu->scores);
    else {
        init_save_score();
        for (uint8_t i = 0; i < NB_GAME; i++)
            menu->scores[i] = 0;
    }
    change_score(menu, menu->scores[menu->cursor]);
    SHOW_SPRITES;
}

static void moveCursorDown(menu_state *menu)
{
    menu->cursor = (menu->cursor + 1) % MENU_ENTRY_COUNT;
    move_sprite(MENU_CURSOR, 28, 56 + 16 * menu->cursor);
    sound_channel1(0x00, 0x81, 0x43, 0x73, 0x86);
    change_score(menu, menu->scores[menu->cursor]);
}

static void moveCursorUp(menu_state *menu)
{
    menu->cursor = (menu->cursor == 0)
        ? MENU_ENTRY_COUNT - 1
        : menu->cursor - 1;
    move_sprite(MENU_CURSOR, 28, 56 + 16 * menu->cursor);
    sound_channel1(0x00, 0x81, 0x43, 0x73, 0x86);
    change_score(menu, menu->scores[menu->cursor]);
}

game_state_t m_update(menu_state *menu,
    const input_state *input)
{
    uint8_t pressed = get_just_pressed(input);
    sound_update(&menu->musics[MENU_THEME]);

    if (pressed & J_DOWN)
        moveCursorDown(menu);
    if (pressed & J_UP)
        moveCursorUp(menu);
    if (pressed & J_A)
        return (game_state_t)(STATE_GAME1 + menu->cursor);
    return STATE_MENU;
}