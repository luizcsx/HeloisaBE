#include <genesis.h>
#include "title.h"
#include "resources.h"

static u16 blink_timer;
static u16 start_visible;

void title_init(void)
{
    VDP_setScreenWidth320();
    PAL_setPalette(PAL0, title_bg.palette->data, DMA);
    VDP_drawImageEx(BG_A, &title_bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, TRUE);

    VDP_setTextPalette(PAL0);
    VDP_setTextPlane(BG_B);

    blink_timer = 0;
    start_visible = TRUE;

    SND_PCM_startPlay(title_bgm, sizeof(title_bgm), SOUND_PCM_RATE_13400, SOUND_PAN_CENTER, TRUE);
}

void title_update(void)
{
    blink_timer++;

    if (blink_timer >= 30)
    {
        blink_timer = 0;
        start_visible = !start_visible;

        if (start_visible)
            VDP_drawText("APERTE START!", 12, 25);
        else
            VDP_clearTextArea(12, 25, 16, 1);
    }
}
