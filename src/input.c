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

void readInput(input_state *input)
{
    input->previous = input->current;
    input->current = joypad();
    input->justPressed = input->current & ~input->previous;
}

inline uint8_t getHeld(const input_state *input)
{
    return input->current;
}

inline uint8_t getJustPressed(const input_state *input)
{
    return input->justPressed;
}
