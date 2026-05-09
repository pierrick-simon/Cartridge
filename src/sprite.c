/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** sprite
*/

#include <gb/gb.h>
#include "sprite.h"

void init_vram_sprite(const uint8_t *data, uint8_t size,
    uint8_t *nb_vram, vram_sprite_t *vram)
{
    uint8_t start = 0;

    if (*nb_vram != 0)
        start = vram[*nb_vram - 1].end;
    vram[*nb_vram].start = start;
    vram[*nb_vram].end = start + size;
    set_sprite_data(start, size, data);
    (*nb_vram)++;
}

void init_sprite(uint8_t vram_id, uint8_t nb,
    sprite_t sprites[MAX_SPRITE], const vram_sprite_t *vram)
{
    if (nb >= MAX_SPRITE)
        return;
    sprites[nb].id = nb;
    sprites[nb].vram_id = vram_id;
    sprites[nb].current = vram[vram_id].start;
    sprites[nb].anim_up = 1;
    set_sprite_tile(nb, vram[vram_id].start);
}

void copy_sprite(uint8_t *nb, uint8_t copy, sprite_t sprites[MAX_SPRITE])
{
    if (*nb >= MAX_SPRITE || copy >= MAX_SPRITE)
        return;
    sprites[*nb].id = *nb + 1;
    sprites[*nb].vram_id = sprites[copy].vram_id;
    sprites[*nb].current = sprites[copy].current;
    sprites[*nb].anim_up = 1;
    (*nb)++;
}

void move_up_sprite(sprite_t *sprite, const vram_sprite_t *vram)
{
    const vram_sprite_t *v = &vram[sprite->vram_id];

    sprite->current++;
    if (sprite->current >= v->end)
        sprite->current = v->start;
    set_sprite_tile(sprite->id, sprite->current);
}

void move_down_sprite(sprite_t *sprite, const vram_sprite_t *vram)
{
    const vram_sprite_t *v = &vram[sprite->vram_id];

    sprite->current--;
    if (sprite->current < v->start)
        sprite->current = v->end - 1;
    set_sprite_tile(sprite->id, sprite->current);
}

void move_to_tile(sprite_t *sprite, const vram_sprite_t *vram, uint8_t nb)
{
    if (nb >= vram[sprite->vram_id].end - vram[sprite->vram_id].start)
        return;
    sprite->current = vram[sprite->vram_id].start + nb;
    set_sprite_tile(sprite->id, sprite->current);
}

void move_up_down_sprite(sprite_t *sprite, const vram_sprite_t *vram)
{
    const vram_sprite_t *v = &vram[sprite->vram_id];

    if (sprite->anim_up) {
        if (sprite->current >= v->end - 1)
            sprite->anim_up = 0;
        else
            sprite->current++;
    } else {
        if (sprite->current <= v->start)
            sprite->anim_up = 1;
        else
            sprite->current--;
    }
    set_sprite_tile(sprite->id, sprite->current);
}

void hide_sprite(sprite_t *sprite)
{
    move_sprite(sprite->id, 0, 0);
}