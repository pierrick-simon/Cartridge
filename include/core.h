/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** core
*/

#ifndef CORE_H_
    #define CORE_H_

    #include "types.h"
    #include "input.h"
    #include "menu.h"
    #include "game1.h"
    #include "game2.h"
    #include "game3.h"

typedef struct {
    game_state_t state;
    InputState input;
    MenuState menu;
    Game1State game1;
    Game2State game2;
    Game3State game3;
} AppContext;

typedef void (*init_fn_t)(AppContext *, sound_t bgm[NB_CHANNEL]);
typedef game_state_t (*update_fn_t)(AppContext *, sound_t bgm[NB_CHANNEL]);

// Init wrappers
static void menuInitWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ menuInit(&ctx->menu, bgm); }

static void game1InitWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ game1Init(&ctx->game1, bgm); }

static void game2InitWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ game2Init(&ctx->game2, bgm); }

static void game3InitWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ game3Init(&ctx->game3, bgm); }

// Update wrappers
static game_state_t menuUpdateWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ return menuUpdate(&ctx->menu, &ctx->input, bgm); }

static game_state_t game1UpdateWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ return game1Update(&ctx->game1, &ctx->input, bgm); }

static game_state_t game2UpdateWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ return game2Update(&ctx->game2, &ctx->input, bgm); }

static game_state_t game3UpdateWrap(AppContext *ctx, sound_t bgm[NB_CHANNEL])
{ return game3Update(&ctx->game3, &ctx->input, bgm); }

// Dispatch tables
static init_fn_t init_table[] = {
    menuInitWrap,
    game1InitWrap,
    game2InitWrap,
    game3InitWrap
};

static update_fn_t update_table[] = {
    menuUpdateWrap,
    game1UpdateWrap,
    game2UpdateWrap,
    game3UpdateWrap
};

#endif /* !CORE_H_ */
