/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Mini-game 2
*/

#include <gb/gb.h>
#include "game2.h"
#include "input.h"
#include "spacetile.h"
#include "spaceship1.h"
#include "spaceship2.h"
#include "spaceship3.h"
#include "game2_theme.h"
#include "explosion.h"

static void init_player(Game2State *game)
{
    game->player.vram_id = GAME2_VRAM_SHIP1;
    game->player.nb_skins = 2;
    game->player.x = 160 / 2;
    game->player.y = 144 - 8;
    init_sprite(game->player.vram_id, GAME2_PLAYER, game->sprites, game->vram);
    move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
}

static void init_ammunition(Game2State *game)
{
    for (uint8_t i = 0; i <  NB_AMMUNITION; i++) {
        game->ammunitions[i].shoot = 0;
        game->ammunitions[i].x = 0;
        game->ammunitions[i].y = 0;
        init_sprite(GAME2_VRAM_AMMUNITION, i + GAME2_AMMUNITION1,
            game->sprites, game->vram);
        hide_sprite(&game->sprites[i]);
    }
}

void game2Init(Game2State *game)
{
    game->nb_vram = 0;
    game->bg_x = 0;
    game->bg_y = 0;
    sound_start(&game->musics[GAME2_THEME], 3, game2_theme_music, TRUE, 0x80);
    set_bkg_data(0, 4, space_tiles);
    set_bkg_tiles(0, 0, 32, 32, space_map);
    init_vram_sprite(spaceship1_tiles, SPACESHIP1_SIZE, &game->nb_vram, game->vram);
    init_vram_sprite(spaceship2_tiles, SPACESHIP2_SIZE, &game->nb_vram, game->vram);
    init_vram_sprite(spaceship3_tiles, SPACESHIP3_SIZE, &game->nb_vram, game->vram);
    init_vram_sprite(projectile1_tiles, PROJECTILE1_SIZE, &game->nb_vram, game->vram);
    init_vram_sprite(explosion_tiles, EXPLOSION_SIZE, &game->nb_vram, game->vram);
    init_player(game);
    init_ammunition(game);
    init_sprite(GAME2_VRAM_SHIP3, GAME2_ENEMY1, game->sprites, game->vram);
    game->enemies[0].vram_id = GAME2_VRAM_SHIP3;
    game->enemies[0].show = 1;
    game->enemies[0].x = 160 / 2;
    game->enemies[0].y = 16;
    game->enemies[0].explode = 0;
    SHOW_BKG;
    SHOW_SPRITES;
}

static void change_ship(Game2State *game, uint8_t pressed)
{
    if (!(pressed & J_UP))
        return;
    game->player.vram_id++;
    if (game->player.vram_id >= game->player.nb_skins)
        game->player.vram_id = 0;
    init_sprite(game->player.vram_id, GAME2_PLAYER, game->sprites, game->vram);
    move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
}

static void handle_player(Game2State *game, const InputState *input,
    uint8_t pressed, uint8_t clock)
{
    if (clock % 4 == 0)
        move_up_sprite(&game->sprites[GAME2_PLAYER], game->vram);
    change_ship(game, pressed);
    if (getHeld(input) & J_LEFT) {
        game->bg_x--;
        game->player.x--;
        if (game->player.x < 16) {
            game->player.x = 16;
        }
        move_bkg(game->bg_x, game->bg_y);
        move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
    }
    if (getHeld(input) & J_RIGHT) {
        game->bg_x++;
        game->player.x++;
        if (game->player.x > 160 - 8) {
            game->player.x = 160 - 8;
        }
        move_bkg(game->bg_x, game->bg_y);
        move_sprite(GAME2_PLAYER, game->player.x, game->player.y);
    }
}

static uint8_t shoot(Game2State *game, uint8_t id)
{
    if (game->ammunitions[id].shoot == 1)
        return 0;
    game->ammunitions[id].shoot = 1;
    game->ammunitions[id].x = game->player.x;
    game->ammunitions[id].y = game->player.y;
    return 1;
}

static void handle_ammunition(Game2State *game, uint8_t pressed)
{
    uint8_t launch = 0;

    for (uint8_t i = 0; i < NB_AMMUNITION; i++) {
        if ((pressed & J_A) && launch == 0)
            launch = shoot(game, i);
        if (game->ammunitions[i].shoot == 1) {
            game->ammunitions[i].y--;
            move_sprite(GAME2_AMMUNITION1 + i,
                game->ammunitions[i].x, game->ammunitions[i].y);
            move_up_sprite(&game->sprites[GAME2_AMMUNITION1 + i], game->vram);
        }
        if (game->ammunitions[i].y <= 0)
            game->ammunitions[i].shoot = 0;
    }
}

static void handle_shown_enemy(Game2State *game, uint8_t i, uint8_t clock)
{
    if (clock % 2 == 0)
        move_up_sprite(&game->sprites[i + GAME2_ENEMY1], game->vram);
    move_sprite(i + GAME2_ENEMY1, game->enemies[i].x, game->enemies[i].y);
}

static void handle_explode_enemy(Game2State *game, uint8_t i, uint8_t clock)
{
    sprite_t *sprite = &game->sprites[i + GAME2_ENEMY1];

    if (sprite->anim_up == 0 && sprite->current
        == game->vram[sprite->vram_id].start) {
        game->enemies[i].explode = 0;
        game->enemies[i].show = 1;
        init_sprite(GAME2_VRAM_SHIP3, GAME2_ENEMY1 + i, game->sprites, game->vram);
    } else if (clock % 2 == 0)
        move_up_down_sprite(sprite, game->vram);
}

static void check_hit_enemy(Game2State *game, enemy_t *enemy, uint8_t id)
{
    for (uint8_t i = 0; i < NB_AMMUNITION; i++) {
        if (game->ammunitions[i].shoot == 0)
            continue;
        if (game->ammunitions[i].y == enemy->y + 8
            && game->ammunitions[i].x + 3 > enemy->x + 1
            && game->ammunitions[i].x + 3 < enemy->x + 7) {
            enemy->explode = 1;
            init_sprite(GAME2_VRAM_EXPLOSION, GAME2_ENEMY1 + id, game->sprites, game->vram);
            hide_sprite(&game->sprites[i + GAME2_AMMUNITION1]);
            sound_channel1(0x00, 0x81, 0x43, 0x73, 0x86);
            break;
        }
    }
}

static void handle_enemies(Game2State *game, uint8_t clock)
{
    for (uint8_t i = 0; i < NB_ENEMY; i++) {
        if (game->enemies[i].show == 0)
            continue;
        if (game->enemies[i].explode == 0) {
            handle_shown_enemy(game, i, clock);
            check_hit_enemy(game, &game->enemies[i], i);
        } else
            handle_explode_enemy(game, i, clock);
    }
}

game_state_t game2Update(Game2State *game, const InputState *input)
{
    static uint8_t clock = 0;
    uint8_t pressed = getJustPressed(input);

    // sound_update(&game->musics[GAME2_THEME]);
    handle_player(game, input, pressed, clock);
    handle_ammunition(game, pressed);
    handle_enemies(game, clock);
    game->bg_y--;
    move_bkg(game->bg_x, game->bg_y);
    clock++;
    if (pressed & J_START)
        return STATE_MENU;
    return STATE_GAME2;
}