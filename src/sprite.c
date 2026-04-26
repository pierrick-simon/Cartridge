/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** sprite
*/

#include <gb/gb.h>
#include "sprite.h"

void init_sprite(const uint8_t *sprite, uint8_t size,
    uint8_t *nb, sprite_t sprites[MAX_SPRITE])
{
    uint8_t start = 1;

    if (*nb >= MAX_SPRITE)
        return;
    if (*nb != 0)
        start = sprites[*nb - 1].end;
    sprites[*nb].id = *nb + 1;
    sprites[*nb].start = start;
    sprites[*nb].end = start + size;
    sprites[*nb].current = start;
    sprites[*nb].anim_up = 1;
    set_sprite_data(start, size, sprite);
    set_sprite_tile(*nb + 1, start);
    (*nb)++;
}

void move_up_sprite(sprite_t *sprite)
{
    sprite->current++;
    if (sprite->current == sprite->end)
        sprite->current = sprite->start;
    set_sprite_tile(sprite->id, sprite->current);
}

void move_up_down_sprite(sprite_t *sprite)
{
    if (sprite->anim_up) {
        if (sprite->current == sprite->end - 1)
            sprite->anim_up = 0;
        else
            sprite->current++;

    } else {
        if (sprite->current == sprite->start)
            sprite->anim_up = 1;
        else
            sprite->current--;
    }
    set_sprite_tile(sprite->id, sprite->current);
}