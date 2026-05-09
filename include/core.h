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
    input_state input;
    menu_state menu;
    g1_state game1;
    g2_state game2;
    g3_state game3;
} app_ctx;

typedef void (*init_fn_t)(app_ctx *);
typedef game_state_t (*update_fn_t)(app_ctx *);

// Init wrappers
static void m_init_wrap(app_ctx *ctx)
{ m_init(&ctx->menu); }

static void g1_init_wrap(app_ctx *ctx)
{ g1_init(&ctx->game1); }

static void g2_init_wrap(app_ctx *ctx)
{ g2_init(&ctx->game2); }

static void g3_init_wrap(app_ctx *ctx)
{ g3_init(&ctx->game3); }

// Update wrappers
static game_state_t m_update_wrap(app_ctx *ctx)
{ return m_update(&ctx->menu, &ctx->input); }

static game_state_t g1_update_wrap(app_ctx *ctx)
{ return g1_update(&ctx->game1, &ctx->input); }

static game_state_t g2_update_wrap(app_ctx *ctx)
{ return g2_update(&ctx->game2, &ctx->input); }

static game_state_t g3_update_wrap(app_ctx *ctx)
{ return g3_update(&ctx->game3, &ctx->input); }

// Dispatch tables
static init_fn_t init_table[] = {
    m_init_wrap,
    g1_init_wrap,
    g2_init_wrap,
    g3_init_wrap
};

static update_fn_t update_table[] = {
    m_update_wrap,
    g1_update_wrap,
    g2_update_wrap,
    g3_update_wrap
};

#endif /* !CORE_H_ */
