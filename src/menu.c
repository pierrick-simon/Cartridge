/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Main menu: navigation and state transitions
*/

#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "menu.h"
#include "input.h"
#include "cursor.h"

void printCenterString(const char *str)
{
    size_t len = 0;

    if (!str)
        return;
    len = strlen(str) / 2;
    for (size_t i = 0; i < (20 - len) / 2; i++)
        printf(" ");
    printf("%s\n", str);
}

//clear screen, load menu tiles, draw game entries
void menuInit(MenuState *menu)
{
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;
    printf("\n\n\n\n\n");
    printCenterString("Game 1");
    printf("\n\n");
    printCenterString("Game 2");
    printf("\n\n");
    printCenterString("Game 3");
    set_sprite_data(0, NB_CURSOR_TILE, CursorTiles);
    set_sprite_tile(0, 0);
    SHOW_SPRITES;
    SPRITES_8x8;
    menu->cursor = 0;
    move_sprite(0, 56, 56 + 24 * menu->cursor);
}

static void moveCursorDown(MenuState *menu)
{
    menu->cursor = (menu->cursor + 1) % MENU_ENTRY_COUNT;
    move_sprite(0, 56, 56 + 24 * menu->cursor);
    NR10_REG=0X00;
    NR11_REG=0X81;
    NR12_REG=0X43;
    NR13_REG=0X73;
    NR14_REG=0X86;
}

static void moveCursorUp(MenuState *menu)
{
    menu->cursor = (menu->cursor == 0)
        ? MENU_ENTRY_COUNT - 1
        : menu->cursor - 1;
    move_sprite(0, 56, 56 + 24 * menu->cursor);
    NR10_REG=0X00;
    NR11_REG=0X81;
    NR12_REG=0X43;
    NR13_REG=0X73;
    NR14_REG=0X86;
}

//draw cursor at new pos && update state if game selected
game_state_t menuUpdate(MenuState *menu, const InputState *input)
{
    uint8_t pressed = getJustPressed(input);

    if (pressed & J_DOWN)
        moveCursorDown(menu);
    if (pressed & J_UP)
        moveCursorUp(menu);
    if (pressed & J_A)
        return (game_state_t)(STATE_GAME1 + menu->cursor);
    return STATE_MENU;
}
