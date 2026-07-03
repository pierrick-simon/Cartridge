/*
** EPITECH PROJECT, 2026
** Cartridge
** File description:
** game2_enemy
*/

#include <gb/gb.h>
#include <rand.h>
#include "game2.h"
#include "input.h"

static void check_hit_player(g2_state *game, uint8_t i)
{
    entity_t *ammo = &game->enemies_ammunitions[i];

    if (ammo->x + 4 < game->player.x || ammo->x > game->player.x + 6)
        return;
    if (ammo->y < game->player.y || ammo->y > game->player.y + 8)
        return;
    ammo->show = 0;
    hide_sprite(&game->sprites[GAME2_ENEMIES_AMMUNITION1 + i]);
    g2_change_nb_live(game, 0);
    sound_channel4(0x00, 0xF2, 0x57, 0x80);
}

void g2_handle_enemies_ammunition(g2_state *game)
{
    for (uint8_t i = 0; i < G2_NB_ENEMIES_AMMUNITION; i++) {
        if (game->enemies_ammunitions[i].show == 0)
            continue;
        game->enemies_ammunitions[i].y += 2;
        move_sprite(GAME2_ENEMIES_AMMUNITION1 + i,
            game->enemies_ammunitions[i].x,
            game->enemies_ammunitions[i].y);
        move_up_sprite(&game->sprites[GAME2_ENEMIES_AMMUNITION1 + i], game->vram);
        check_hit_player(game, i);
        if (game->enemies_ammunitions[i].y >= 160)
            game->enemies_ammunitions[i].show = 0;
    }
}

static void move_skin1(g2_state *game, uint8_t i)
{
    enemy_t *enemy = &game->enemies[i];

    enemy->move_timer++;
    if (enemy->move_timer < 3)
        return;
    enemy->move_timer = 0;
    if (enemy->dir == 0) {
        enemy->x--;
        if (enemy->x <= 16)
            enemy->dir = 1;
    } else {
        enemy->x++;
        if (enemy->x >= 152)
            enemy->dir = 0;
    }
}

static void skin1_try_shoot(g2_state *game, enemy_t *enemy)
{
    enemy->timer++;
    if (enemy->timer < G2_ENEMY_SHOOT_DELAY)
        return;
    enemy->timer = 0;
    for (uint8_t i = 0; i < G2_NB_ENEMIES_AMMUNITION; i++) {
        if (game->enemies_ammunitions[i].show == 1)
            continue;
        game->enemies_ammunitions[i].x = enemy->x;
        game->enemies_ammunitions[i].y = enemy->y + 8;
        game->enemies_ammunitions[i].show = 1;
        move_sprite(GAME2_ENEMIES_AMMUNITION1 + i,
            game->enemies_ammunitions[i].x,
            game->enemies_ammunitions[i].y);
        break;
    }
}

static void move_skin2(g2_state *game, uint8_t i)
{
    enemy_t *enemy = &game->enemies[i];

    enemy->move_timer++;
    if (enemy->move_timer < 2)
        return;
    enemy->move_timer = 0;
    if (enemy->x < game->player.x)
        enemy->x++;
    else if (enemy->x > game->player.x)
        enemy->x--;
    enemy->y += 2;
    if (enemy->x + 6 < game->player.x || enemy->x > game->player.x + 6)
        return;
    if (enemy->y + 6 < game->player.y || enemy->y > game->player.y + 6)
        return;
    enemy->explode = 1;
    init_sprite(GAME2_VRAM_EXPLOSION, GAME2_ENEMY1 + i,
        game->sprites, game->vram);
    sound_channel4(0x00, 0xF2, 0x57, 0x80);
    g2_change_nb_live(game, 0);
}

static void handle_shown_enemy(g2_state *game, uint8_t i, uint16_t clock)
{
    enemy_t *enemy = &game->enemies[i];
    uint8_t moved = 0;

    if ((clock & 3) == 0)
        move_up_sprite(&game->sprites[i + GAME2_ENEMY1], game->vram);
    if (enemy->vram_id == GAME2_VRAM_SHIP3) {
        moved = 1;
        move_skin1(game, i);
        skin1_try_shoot(game, enemy);
    } else {
        move_skin2(game, i);
        moved = 1;
    }
    if (moved == 1)
        move_sprite(i + GAME2_ENEMY1, enemy->x, enemy->y);
}

static void handle_explode_enemy(g2_state *game, uint8_t i, uint16_t clock)
{
    sprite_t *sprite = &game->sprites[i + GAME2_ENEMY1];
    uint8_t ship_skin = 0;

    if (sprite->current == game->vram[sprite->vram_id].end - 1) {
        game->enemies[i].explode = 0;
        game->enemies[i].show = 1;
        ship_skin = (rand() % G2_NB_ENEMY_SKIN) + GAME2_VRAM_SHIP3;
        game->enemies[i].vram_id = ship_skin;
        game->enemies[i].timer = 0;
        game->enemies[i].x = rand() % 160 + 8;
        game->enemies[i].y = rand() % 50 + 20;
        init_sprite(ship_skin, GAME2_ENEMY1 + i, game->sprites, game->vram);
    } else if ((clock & 1) == 0)
        move_up_sprite(sprite, game->vram);
}

static void add_power_up(g2_state *game, enemy_t *enemy)
{
    uint8_t tile = 1;

    if (rand() % 10 != 0)
        return;
    for (uint8_t i = 0; i < G2_NB_POWER_UP; i++) {
        if (game->power_up[i].show == 1)
            continue;
        game->power_up[i].show = 1;
        game->power_up[i].x = enemy->x;
        game->power_up[i].y = enemy->y;
        if (game->score > 150 && game->player.vram_id != GAME2_VRAM_SHIP2)
            tile = rand() % 2;
        move_to_tile(&game->sprites[GAME2_POWER_UP1 + i], game->vram, tile);
        break;
    }
}

static void check_hit_enemy(g2_state *game, enemy_t *enemy, uint8_t id)
{
    for (uint8_t j = 0; j < G2_NB_AMMUNITION; j++) {
        if (game->ammunitions[j].show == 0)
            continue;
        if (game->ammunitions[j].y < enemy->y
            || game->ammunitions[j].y > enemy->y + 8)
            continue;
        if (game->ammunitions[j].x + 3 <= enemy->x + 1
            || game->ammunitions[j].x + 3 >= enemy->x + 7)
            continue;
        game->ammunitions[j].show = 0;
        hide_sprite(&game->sprites[j + GAME2_AMMUNITION1]);
        enemy->explode = 1;
        init_sprite(GAME2_VRAM_EXPLOSION, GAME2_ENEMY1 + id,
            game->sprites, game->vram);
        sound_channel4(0x00, 0xF2, 0x57, 0x80);
        if (enemy->vram_id == GAME2_VRAM_SHIP4)
            g2_change_score(game, 5);
        else
            g2_change_score(game, 10);
        add_power_up(game, enemy);
        break;
    }
}

void g2_handle_enemies(g2_state *game, uint16_t clock)
{
    for (uint8_t i = 0; i < G2_NB_ENEMY; i++) {
        if (game->enemies[i].show == 0)
            continue;
        if (game->enemies[i].explode == 0) {
            handle_shown_enemy(game, i, clock);
            check_hit_enemy(game, &game->enemies[i], i);
        } else
            handle_explode_enemy(game, i, clock);
        move_sprite(i + GAME2_ENEMY1,
            game->enemies[i].x, game->enemies[i].y);
    }
}
