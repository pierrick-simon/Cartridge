/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Main menu: navigation and state transitions
*/

#include <gb/gb.h>
#include <stdint.h>
#include "menu.h"
#include "input.h"

//clear screen, load menu tiles, draw game entries
void menuInit(MenuState *menu)
{
    menu->cursor = 0;
}

static void moveCursorDown(MenuState *menu)
{
    menu->cursor = (menu->cursor + 1) % MENU_ENTRY_COUNT;
}

static void moveCursorUp(MenuState *menu)
{
    menu->cursor = (menu->cursor == 0)
        ? MENU_ENTRY_COUNT - 1
        : menu->cursor - 1;
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
