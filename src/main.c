/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Entry point, state machine, main game loop
*/

#include <gb/gb.h>
#include <string.h>
#include "core.h"

void clear_screen(void) {
    uint8_t blank[20 * 18];
    memset(blank, 0, sizeof(blank));
    set_bkg_tiles(0, 0, 20, 18, blank);
}

static void transitionTo(AppContext *ctx, game_state_t next)
{
    if (next == ctx->state)
        return;
    ctx->state = next;
    init_table[ctx->state](ctx);
    vsync();
    clear_screen();
}

inline static game_state_t dispatchUpdate(AppContext *ctx)
{
    return update_table[ctx->state](ctx);
}

// DISPLAY_ON GBDK, macro turns on display after init
void main(void)
{
    static AppContext ctx = {.state = INIT_STATE};

    init_table[ctx.state](&ctx);
    DISPLAY_ON;

    while (1) {
        wait_vbl_done();
        readInput(&ctx.input);
        transitionTo(&ctx, dispatchUpdate(&ctx));
    }
}
