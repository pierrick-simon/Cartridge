/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** sprite
*/

#ifndef SPRITE_H_
    #define SPRITE_H_

    #include <stdint.h>

    #define MAX_SPRITE      40

    typedef struct {
        uint8_t start;
        uint8_t end;
    } vram_sprite_t;

    typedef struct {
        uint8_t id;
        uint8_t vram_id;
        uint8_t current;
        uint8_t anim_up;
    } sprite_t;

void init_vram_sprite(
    const uint8_t *data, uint8_t size,
    uint8_t *nb_vram, vram_sprite_t *vram);

void init_sprite(uint8_t vram_id, uint8_t nb,
    sprite_t sprites[MAX_SPRITE], const vram_sprite_t *vram);
void copy_sprite(uint8_t *nb, uint8_t copy, sprite_t sprites[MAX_SPRITE]);

void move_to_tile(sprite_t *sprite, const vram_sprite_t *vram, uint8_t nb);
void move_up_sprite(sprite_t *sprite, const vram_sprite_t *vram);
void move_down_sprite(sprite_t *sprite, const vram_sprite_t *vram);
void move_up_down_sprite(sprite_t *sprite, const vram_sprite_t *vram);
void hide_sprite(sprite_t *sprite);

#endif