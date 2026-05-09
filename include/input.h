/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Joypad input reading and edge detection
*/

#ifndef INPUT_H
    #define INPUT_H

    #include <stdint.h>

typedef struct {
    uint8_t current;
    uint8_t previous;
    uint8_t justPressed;
} input_state;

void readInput(input_state *input);
uint8_t getHeld(const input_state *input);
uint8_t getJustPressed(const input_state *input);

#endif
