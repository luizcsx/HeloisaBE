#include <genesis.h>
#include "title.h"
#include "resources.h"
#include "game_state.h"

static u16 blink_timer;
static u16 start_visible;
static bool fading_out;

#define APERTE_START_TILE_X  7
#define APERTE_START_TILE_Y  24
#define APERTE_START_TILE_W  26
#define APERTE_START_TILE_H  9
#define APERTE_START_TILE_INDEX (TILE_USER_INDEX + 1120)

#define FADE_FRAMES  30

void title_init(void)
{
    VDP_setScreenWidth320();
    PAL_setPalette(PAL0, palette_black, DMA);

    VDP_drawImageEx(BG_A, &title_bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, TRUE);

    VDP_drawImageEx(BG_B, &aperte_start, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, APERTE_START_TILE_INDEX),
                     APERTE_START_TILE_X, APERTE_START_TILE_Y, FALSE, TRUE);

    blink_timer = 0;
    start_visible = TRUE;
    fading_out = FALSE;

    SND_PCM_startPlay(title_bgm, sizeof(title_bgm), SOUND_PCM_RATE_13400, SOUND_PAN_CENTER, TRUE);

    PAL_fadeIn(0, 15, title_bg.palette->data, FADE_FRAMES, FALSE);
}

static void title_update_fade_out(void)
{
    if (!PAL_isDoingFade())
    {
        SND_PCM_stopPlay();
        game_state = STATE_MENU;
    }
}

void title_update(void)
{
    u16 joy;

    if (fading_out)
    {
        title_update_fade_out();
        return;
    }

    joy = JOY_readJoypad(JOY_1);

    if (joy & BUTTON_START)
    {
        fading_out = TRUE;
        PAL_fadeOut(0, 15, FADE_FRAMES, FALSE);
        return;
    }

    blink_timer++;

    if (blink_timer >= 30)
    {
        blink_timer = 0;
        start_visible = !start_visible;

        if (start_visible)
            VDP_drawImageEx(BG_B, &aperte_start, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, APERTE_START_TILE_INDEX),
                             APERTE_START_TILE_X, APERTE_START_TILE_Y, FALSE, TRUE);
        else
            VDP_clearTileMapRect(BG_B, APERTE_START_TILE_X, APERTE_START_TILE_Y,
                                  APERTE_START_TILE_W, APERTE_START_TILE_H);
    }
}
