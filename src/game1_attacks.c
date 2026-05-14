/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_attacks
*/

#include <gb/gb.h>
#include <stdio.h>
#include "game1.h"

static void lunch_star(star_t *star, uint16_t clock,
    uint8_t speed, uint16_t nb_tick)
{
    uint16_t dir = ((clock * 61 + 69)) & 2;

    star->orientation = (clock * 531) & 1;
    if (!star->orientation) {
        star->y.b.h = ((clock * 969 + 3) % (10 * 8)) + 16 + 3 * 8;
        if (dir & 1)
            star->x.b.h = 0;
        else
            star->x.b.h = 168;
    } else {
        star->x.b.h = ((clock * 676 + 9) % (14 * 8)) + 8 + 3 * 8;
        if (dir & 1)
                star->y.b.h = 8;
            else
                star->y.b.h = 144;
    }
    star->speed = (G1_DELTA_STAR_SPEED - (speed *
        G1_DELTA_STAR_SPEED / 10)) + G1_MAX_STAR_SPEED;
    star->timer = nb_tick;
}

static void lunch_asteroid(asteroid_t *asteroid, uint16_t clock,
    uint8_t speed, uint16_t nb_tick)
{
    uint16_t dir = ((clock * 61 + 69)) & 3;

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
}

static void move_star(star_t *star, uint8_t clock, const palyer_t *player)
{
    int16_t v_x = (player->x.w - star->x.w);
    int16_t v_y = (player->y.w - star->y.w);

    star->x.w += v_x / star->speed;
    star->y.w += v_y / star->speed;
    if (star->timer == 0) {
        move_sprite(GAME1_STAR, 0, 0);
        star->here = 0;
        return;
    }
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
    int8_t distx = 0;
    int8_t disty = 0;

    distx = (int8_t)x1 - (int8_t)x2;
    disty = (int8_t)y1 - (int8_t)y2;
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
    if (game->player.dash_timer != 0 || game->player.cd_timer != 0)
        return;
    for (uint8_t i = 0; i < G1_NB_ASTEROID; ++i) {
        if (&game->asteroid[i].here == 1 ||
                is_hit(game->asteroid[i].x, game->asteroid[i].y,
                game->player.x.b.h, game->player.y.b.h)) {
            collide(&game->player);
            return;
        }
    }
    if (&game->star.here == 1 || is_hit(game->star.x.b.h, game->star.y.b.h,
            game->player.x.b.h, game->player.y.b.h))
        collide(&game->player);
}

void g1_handle_attacks(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock)
{
    for (uint8_t i = 0; i < G1_NB_ASTEROID; ++i)
        simulate_asteroid(&game->asteroid[i], clock, i);
    collision(game);
    move_star(&game->star, clock, &game->player);
    if (pressed & J_B) {
        change_nb_live(&game->player, 1);
        change_nb_live(&game->player, 1);
        change_nb_live(&game->player, 1);
        lunch_star(&game->star, clock, 10, 10000);
    }
}
