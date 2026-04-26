#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "menu.h"
#include "input.h"
#include "cursor.h"
#include "starwars.h"

void printCenterString(const char *str)
{
    size_t len = 0;

    if (!str)
        return;
    len = strlen(str);
    for (size_t i = 0; i < (20 - len) / 2; i++)
        printf(" ");
    printf("%s\n", str);
}

void menuInit(MenuState *menu)
{
    sound_start(&menu->musics[MENU_THEME], 3, starwars_music, TRUE, 0xFF);
    printf("\n\n\n\n\n");
    printCenterString("Game 1");
    printf("\n\n");
    printCenterString("Game 2");
    printf("\n\n");
    printCenterString("Game 3");
    set_sprite_data(0, NB_CURSOR_TILE, CursorTiles);
    set_sprite_tile(0, 0);
    menu->cursor = 0;
    SHOW_SPRITES;
    move_sprite(0, 56, 56 + 24 * menu->cursor);
}

static void moveCursorDown(MenuState *menu)
{
    menu->cursor = (menu->cursor + 1) % MENU_ENTRY_COUNT;
    move_sprite(0, 56, 56 + 24 * menu->cursor);
    sound_channel1(0x00, 0x81, 0x43, 0x73, 0x86);
}

static void moveCursorUp(MenuState *menu)
{
    menu->cursor = (menu->cursor == 0)
        ? MENU_ENTRY_COUNT - 1
        : menu->cursor - 1;
    move_sprite(0, 56, 56 + 24 * menu->cursor);
    sound_channel1(0x00, 0x81, 0x43, 0x73, 0x86);
}

game_state_t menuUpdate(MenuState *menu,
    const InputState *input)
{
    uint8_t pressed = getJustPressed(input);
    sound_update(&menu->musics[MENU_THEME]);

    if (pressed & J_DOWN)
        moveCursorDown(menu);
    if (pressed & J_UP)
        moveCursorUp(menu);
    if (pressed & J_A)
        return (game_state_t)(STATE_GAME1 + menu->cursor);
    return STATE_MENU;
}