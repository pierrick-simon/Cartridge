/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Joypad input reading and just-pressed detection
*/

#include <gb/gb.h>
#include <stdint.h>
#include "input.h"

// input->justPressed = input->current & ~input->previous;
// keeps buttons that are currently pressed but were not in the previous state
// by keeping bits set in current but not in previous

void readInput(InputState *input)
{
    input->previous = input->current;
    input->current = joypad();
    input->justPressed = input->current & ~input->previous;
}

uint8_t getHeld(const InputState *input)
{
    return input->current;
}

uint8_t getJustPressed(const InputState *input)
{
    return input->justPressed;
}
