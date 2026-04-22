/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** types and state definitions
*/

#ifndef TYPES_H
    #define TYPES_H

    #include <stdint.h>

typedef enum {
    STATE_MENU = 0,
    STATE_GAME1 = 1,
    STATE_GAME2 = 2,
    STATE_GAME3 = 3
} game_state_t;

    #define INIT_STATE STATE_GAME1

#endif
