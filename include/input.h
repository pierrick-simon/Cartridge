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
} InputState;

void readInput(InputState *input);
uint8_t getHeld(const InputState *input);
uint8_t getJustPressed(const InputState *input);

#endif
