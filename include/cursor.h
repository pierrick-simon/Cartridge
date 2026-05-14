/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** cursor
*/

#ifndef CURSOR_H
    #define CURSOR_H

    typedef enum {
        CURSOR_TILE,
        NB_CURSOR_TILE,
    } cursor_t;

    extern const unsigned char CursorTiles[];

#endif