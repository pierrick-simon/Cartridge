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

static void printCenterString(const char *str)
{
    size_t len = 0;

    if (!str)
        return;
    len = strlen(str);
    for (size_t i = 0; i < (20 - len) / 2; i++)
        printf(" ");
    printf("%s\n", str);
}

static void m_init_sprite(menu_state *menu)
{
    init_sprite(MENU_VRAM_CURSOR, MENU_CURSOR, menu->sprites, menu->vram);
    move_sprite(MENU_CURSOR, 56, 56 + 24 * menu->cursor);
    for (uint8_t i = 0; i < M_NB_NUMBER; i++) {
        init_sprite(MENU_VRAM_NUMBER, MENU_SCORE1 + i,
            menu->sprites, menu->vram);
        move_sprite(MENU_SCORE1 + i, 70 + 6 * i, 130);
    }
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
    printf("\n\n\n\n\n");
    printCenterString("Game 1");
    printf("\n\n");
    printCenterString("Game 2");
    printf("\n\n");
    printCenterString("Game 3");
    init_vram_sprite(CursorTiles, NB_CURSOR_TILE, &menu->nb_vram, menu->vram);
    init_vram_sprite(number_tiles, NUMBER_SIZE, &menu->nb_vram, menu->vram);
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
    move_sprite(MENU_CURSOR, 56, 56 + 24 * menu->cursor);
    sound_channel1(0x00, 0x81, 0x43, 0x73, 0x86);
    change_score(menu, menu->scores[menu->cursor]);
}

static void moveCursorUp(menu_state *menu)
{
    menu->cursor = (menu->cursor == 0)
        ? MENU_ENTRY_COUNT - 1
        : menu->cursor - 1;
    move_sprite(MENU_CURSOR, 56, 56 + 24 * menu->cursor);
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