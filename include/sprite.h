/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** sprite
*/

#ifndef SPRITE_H_
    #define SPRITE_H_

    #include <stdint.h>

    #define MAX_SPRITE 40

    typedef struct {
        uint8_t id;
        uint8_t start;
        uint8_t end;
        uint8_t current;
        uint8_t anim_up;
    } sprite_t;

void init_sprite(const uint8_t *sprite, uint8_t size,
    uint8_t *nb, sprite_t sprites[MAX_SPRITE]);

void move_up_down_sprite(sprite_t *sprite);
void move_up_sprite(sprite_t *sprite);
void hide_sprite(sprite_t *sprite);

#endif

