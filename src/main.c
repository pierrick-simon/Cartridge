/*
** EPITECH PROJECT, 2026
** cartridge
** File description:
** Entry point, state machine, main game loop
*/

#include <gb/gb.h>
#include <string.h>
#include "core.h"
#include "sound_manager.h"

void clear_screen(void)
{
    uint8_t empty_tile[16] = {0};
    for (uint8_t i = 0; i < 192; i++)
        set_bkg_data(i, 1, empty_tile);
    for (uint8_t i = 0; i < 192; i++)
        set_sprite_data(i, 1, empty_tile);
}

static void transitionTo(AppContext *ctx, game_state_t next)
{
    if (next == ctx->state)
        return;
    for (size_t i = 1; i <= NB_CHANNEL; i++)
        mute_channel(i);
    clear_screen();
    ctx->state = next;
    init_table[ctx->state](ctx);
    vsync();
}

static game_state_t dispatchUpdate(AppContext *ctx)
{
    return update_table[ctx->state](ctx);
}

// DISPLAY_ON GBDK, macro turns on display after init
void main(void)
{
    static AppContext ctx = {.state = INIT_STATE};

    init_table[ctx.state](&ctx);
    DISPLAY_ON;
    sound_init();
    while (1) {
        wait_vbl_done();
        readInput(&ctx.input);
        transitionTo(&ctx, dispatchUpdate(&ctx));
    }
}
