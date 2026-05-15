/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_attacks
*/

#include <gb/gb.h>
#include <stdio.h>
#include "game1.h"
#include <rand.h>

static void lunch_star(g1_state *game, uint32_t clock,
    uint8_t speed, uint16_t nb_tick)
{
    star_t *star = &game->star;
    uint16_t dir = clock * 61 + 69;

    star->orientation = (clock * 531) & 1;
    if (!star->orientation) {
        star->y.b.h = ((clock * 969 + 3) % (10 * 8)) + 16 + 3 * 8;
        if (dir & 2)
            star->x.b.h = 0;
        else
            star->x.b.h = 168;
    } else {
        star->x.b.h = ((clock * 676 + 9) % (14 * 8)) + 8 + 3 * 8;
        if (dir & 2)
                star->y.b.h = 8;
            else
                star->y.b.h = 144;
    }
    star->explode_timer = -1;
    star->here = 1;
    star->speed = (G1_DELTA_STAR_SPEED - (speed *
        G1_DELTA_STAR_SPEED / 10)) + G1_MAX_STAR_SPEED;
    star->timer = nb_tick;
    init_sprite(GAME1_VRAM_STAR, GAME1_STAR,
            game->sprites, game->vram);
}

static void lunch_asteroid(g1_state *game, uint8_t i,
    uint8_t speed, uint16_t nb_tick)
{
    uint8_t clock = game->clock;
    asteroid_t *asteroid = &game->asteroid[i];
    uint16_t dir = clock * 61 + 69;
    uint8_t flip = ((clock * 211) % 4);
    uint8_t prop = 0;

    asteroid->v_x = dir & G1_X ? speed: (speed * -1);
    asteroid->v_y = dir & G1_Y ? speed: (speed * -1);
    asteroid->orientation = (clock * 531) & 1;
    if (!asteroid->orientation) {
        asteroid->y = ((clock * 969 + 3) % (10 * 8)) + 16 + 3 * 8;
        if (asteroid->v_x > 0)
            asteroid->x = 0;
        else
            asteroid->x = 168;
    } else {
        asteroid->x = ((clock * 676 + 9) % (14 * 8)) + 8 + 3 * 8;
    if (asteroid->v_y > 0)
            asteroid->y = 8;
        else
            asteroid->y = 144;
    }
    asteroid->speed = speed;
    asteroid->timer = nb_tick;
    asteroid->here = 1;
    flip & 1 ? prop += S_FLIPX: 0;
    flip & 2 ? prop += S_FLIPY: 0;
    set_sprite_prop(GAME1_F_ASTEROID + i, flip);
}

static inline uint32_t get_nb_tick(uint32_t clock)
{
    if (clock > 9000)
        clock = 9000;
    return ((clock * (2000)) / 9000) + 500;
}

static void lunch_attack(g1_state *game)
{
    if (game->star.here == 0 && (rand() % 2) == 0)
        return lunch_star(game, game->clock, game->clock / (60 * 15),
            get_nb_tick(game->clock) * 2);
    for (uint8_t i = 0; i < game->max_asteroid; ++i)
        if (game->asteroid[i].here == 0)
            return lunch_asteroid(game, i,
                game->clock > 900 ? 2: 1, get_nb_tick(game->clock));
    if (game->star.here == 0)
        lunch_star(game, game->clock, game->clock / (60 * 15),
            get_nb_tick(game->clock) * 2);
}

static void move_star(g1_state *game, uint8_t clock)
{
    star_t *star = &game->star;
    int16_t v_x = (game->player.x.w - star->x.w);
    int16_t v_y = (game->player.y.w - star->y.w);
    
    if (star->explode_timer == 0) {
        star->here = 0;
        move_sprite(GAME1_STAR, 0, 0);
        return;
    }
    if (star->timer == 0 && star->explode_timer != 0)
        --star->explode_timer;
    if (star->timer != 0)
        --star->timer;
    if (star->timer == 0 && star->explode_timer == -1) {
        star->explode_timer = G1_STAR_EXPLODE_TIMER;
        init_sprite(GAME1_VRAM_EXPLOSION, GAME1_STAR,
            game->sprites, game->vram);
        return;
    }
    if (star->explode_timer != -1) {
        if (star->explode_timer & 3)
            move_up_sprite(&game->sprites[GAME1_STAR], game->vram);
        return;
    }
    star->x.w += v_x / star->speed;
    star->y.w += v_y / star->speed;
    move_sprite(GAME1_STAR, star->x.b.h + 1, star->y.b.h + 1);
}

static void move_asteroid(asteroid_t *asteroid, uint8_t clock, uint8_t i)
{
    if (asteroid->orientation || (clock & 2) == 0)
        asteroid->x += asteroid->v_x;
    if (!asteroid->orientation || (clock & 2) == 0)
        asteroid->y += asteroid->v_y;
    if (asteroid->timer == 0) {
        if (asteroid->x < 0 || asteroid->x > 168 || asteroid->y < 8 || asteroid->y > 144) {
            move_sprite(GAME1_F_ASTEROID + i, 0, 0);
            asteroid->here = 0;
        } else
            move_sprite(GAME1_F_ASTEROID + i, asteroid->x, asteroid->y);
        return;
    }
    if (asteroid->y < 8 + 8)
        asteroid->v_y = asteroid->speed;
    if (asteroid->y > 144 - 8)
        asteroid->v_y = asteroid->speed * -1;
    if (asteroid->x > 160)
        asteroid->v_x = asteroid->speed * -1;
    if (asteroid->x < 8)
        asteroid->v_x = asteroid->speed;
    move_sprite(GAME1_F_ASTEROID + i, asteroid->x, asteroid->y);
}

static void simulate_asteroid(asteroid_t *asteroid, uint8_t clock, uint8_t i)
{
    if (asteroid->here == 0)
        return;
    if (asteroid->timer != 0)
        --asteroid->timer;
    move_asteroid(asteroid, clock, i);
}

static inline uint8_t is_hit(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    int16_t distx = 0;
    int16_t disty = 0;

    distx = (int16_t)x1 - (int16_t)x2;
    disty = (int16_t)y1 - (int16_t)y2;
    if (distx <= 8 && distx >= -8 && disty <= 8 && disty >= -8)
        return 1;
    return 0;
}

static void collide(palyer_t *player)
{
    change_nb_live(player, 0);
    player->cd_timer = G1_CD_TIMER;
}

static void collision(g1_state *game)
{
    if (game->player.dash_timer != 0)
        return;
    for (uint8_t i = 0; i < game->max_asteroid; ++i) {
        if (game->asteroid[i].here == 1 && game->player.cd_timer == 0 &&
                is_hit(game->asteroid[i].x, game->asteroid[i].y,
                game->player.x.b.h, game->player.y.b.h
            )) {
            collide(&game->player);
            sound_channel4(0x00, 0xF2, 0x57, 0x80);
            return;
        }
    }
    if (game->star.timer != 0 && is_hit(game->star.x.b.h, game->star.y.b.h,
            game->player.x.b.h, game->player.y.b.h)) {
        if (game->player.cd_timer == 0) {
            collide(&game->player);
        }
        sound_channel1(0x2A, 0x80, 0xF1, 0xA9, 0x87);
        init_sprite(GAME1_VRAM_EXPLOSION, GAME1_STAR,
            game->sprites, game->vram);
        game->star.timer = 0;
        game->star.explode_timer = G1_STAR_EXPLODE_TIMER;
    }
}

void g1_handle_attacks(g1_state *game, const input_state *input,
    uint8_t pressed)
{
    for (uint8_t i = 0; i < game->max_asteroid; ++i)
        simulate_asteroid(&game->asteroid[i], game->clock, i);
    if (game->star.here == 1)
        move_star(game, game->clock);
    collision(game);
    if (game->spawn_timer == 0) {
        lunch_attack(game);
        game->spawn_timer = G1_ATTACK_COOLDOWN;
    }
}
