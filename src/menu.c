#include <genesis.h>
#include "menu.h"
#include "game_state.h"
#include "save.h"
#include "resources.h"

#define MENU_OPT_NEW_GAME  0
#define MENU_OPT_CONTINUE  1
#define MENU_OPT_OPTIONS   2
#define MENU_OPT_COUNT     3

#define MENU_BASE_X  10
#define MENU_BASE_Y  12
#define MENU_LINE_H  2

static const char* menu_labels[MENU_OPT_COUNT] =
{
    "NOVO JOGO",
    "CONTINUAR",
    "OPCOES"
};

static s16 menu_cursor;
static bool has_save;

static void menu_draw_option(u16 index, bool selected)
{
    u16 palette = selected ? PAL1 : PAL0;
    bool enabled = (index != MENU_OPT_CONTINUE) || has_save;

    if (!enabled)
        palette = PAL2;

    VDP_setTextPalette(palette);
    VDP_drawText(menu_labels[index], MENU_BASE_X, MENU_BASE_Y + (index * MENU_LINE_H));
}

static void menu_draw_all(void)
{
    u16 i;

    for (i = 0; i < MENU_OPT_COUNT; i++)
        menu_draw_option(i, i == menu_cursor);
}

static void menu_move_cursor(s16 dir)
{
    s16 previous = menu_cursor;

    menu_cursor += dir;

    if (menu_cursor < 0)
        menu_cursor = MENU_OPT_COUNT - 1;
    else if (menu_cursor >= MENU_OPT_COUNT)
        menu_cursor = 0;

    menu_draw_option(previous, FALSE);
    menu_draw_option(menu_cursor, TRUE);
}

static void menu_confirm(void)
{
    switch (menu_cursor)
    {
        case MENU_OPT_NEW_GAME:
            game_state = STATE_GAME;
            break;

        case MENU_OPT_CONTINUE:
            if (has_save)
                game_state = STATE_GAME;
            break;

        case MENU_OPT_OPTIONS:
            XGM2_playPCM(stage_bgm, sizeof(stage_bgm), SOUND_PCM_CH2);
            break;
    }
}

void menu_init(void)
{
    menu_cursor = MENU_OPT_NEW_GAME;
    has_save = save_exists();

    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);

    PAL_setColor((PAL0 * 16), RGB24_TO_VDPCOLOR(0x246024));
    VDP_setBackgroundColor((PAL0 * 16));

    PAL_setColors((PAL1 * 16), palette_black, 1, DMA);
    PAL_setColor((PAL1 * 16) + 1, RGB24_TO_VDPCOLOR(0xFFD700));

    PAL_setColors((PAL2 * 16), palette_black, 1, DMA);
    PAL_setColor((PAL2 * 16) + 1, RGB24_TO_VDPCOLOR(0x555555));

    menu_draw_all();
}

void menu_update(void)
{
    u16 joy = JOY_readJoypad(JOY_1);

    if (joy & BUTTON_UP)
        menu_move_cursor(-1);
    else if (joy & BUTTON_DOWN)
        menu_move_cursor(1);
    else if (joy & (BUTTON_START | BUTTON_A))
        menu_confirm();
}
