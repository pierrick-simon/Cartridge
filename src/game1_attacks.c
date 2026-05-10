/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** game1_attacks
*/

#include <gb/gb.h>
#include <stdio.h>
#include "game1.h"

static void lunch_asteroid(asteroid_t *asteroid, uint16_t clock,
    uint8_t speed, uint16_t nb_tick)
{
    uint16_t dir = (clock * 424) % 4;

    asteroid->x = ((clock * 676) % (14 * 8)) + 8 + 3 * 8;
    asteroid->y = ((clock * 969) % (10 * 8)) + 16 + 3 * 8;
    asteroid->v_x = dir & G1_X ? speed: -speed;
    asteroid->v_y = dir & G1_Y ? speed: -speed;
    asteroid->timer = nb_tick;
    asteroid->orientation = (clock * 531) % 2;

}

static void move_asteroid(asteroid_t *asteroid)
{
    if (asteroid->orientation || (asteroid->timer % 2) == 0)
        asteroid->x += asteroid->v_x;
    if (!asteroid->orientation || (asteroid->timer % 2) == 0)
        asteroid->y += asteroid->v_y;
    if (asteroid->y < 8 + 8) {
        asteroid->y = 8 + 8;
        asteroid->v_y *= -1;
    }
    if (asteroid->y > 144 - 8) {
        asteroid->y = 144 - 8;
        asteroid->v_y *= -1;
    }
    if (asteroid->x > 160) {
        asteroid->x = 160;
        asteroid->v_x *= -1;
    }
    if (asteroid->x < 8) {
        asteroid->x = 8;
        asteroid->v_x *= -1;
    }
}

static void simulate_asteroid(asteroid_t *asteroid)
{
    if (asteroid->timer == 0)
        return;
    if (asteroid->timer == 1)
        return move_sprite(GAME1_ASTEROID, 0, 0);
    --asteroid->timer;
    move_asteroid(asteroid);
    move_sprite(GAME1_ASTEROID, asteroid->x, asteroid->y);
}

static inline void asteroid_hit(const asteroid_t *asteroid, palyer_t *player)
{
    int8_t distx = 0;
    int8_t disty = 0;

    if (asteroid->timer == 0 || player->cd_timer != 0)
        return;
    distx = (int8_t)asteroid->x - (int8_t)player->x.b.h;
    disty = (int8_t)asteroid->y - (int8_t)player->y.b.h;
    if (distx <= 8 && distx >= -8 && disty <= 8 && disty >= -8) {
        change_nb_live(player, 0);
        player->cd_timer = G1_CD_TIMER;
    }
}

static void collision(g1_state *game)
{
    asteroid_hit(&game->asteroid, &game->player);
}

void g1_handle_attacks(g1_state *game, const input_state *input,
    uint8_t pressed, uint8_t clock)
{
    simulate_asteroid(&game->asteroid);
    collision(game);
    if (pressed & J_B) {
        change_nb_live(&game->player, 1);
        change_nb_live(&game->player, 1);
        change_nb_live(&game->player, 1);
        lunch_asteroid(&game->asteroid, clock, 2, 1000);
    }
}
