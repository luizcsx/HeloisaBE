#include <genesis.h>
#include "title.h"
#include "resources.h"

static u16 blink_timer;
static u16 start_visible;

#define APERTE_START_TILE_X  7
#define APERTE_START_TILE_Y  24
#define APERTE_START_TILE_W  26
#define APERTE_START_TILE_H  9
#define APERTE_START_TILE_INDEX (TILE_USER_INDEX + 1120)

void title_init(void)
{
    VDP_setScreenWidth320();
    PAL_setPalette(PAL0, title_bg.palette->data, DMA);
    VDP_drawImageEx(BG_A, &title_bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, TRUE);

    VDP_drawImageEx(BG_B, &aperte_start, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, APERTE_START_TILE_INDEX),
                     APERTE_START_TILE_X, APERTE_START_TILE_Y, FALSE, TRUE);

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
            VDP_drawImageEx(BG_B, &aperte_start, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, APERTE_START_TILE_INDEX),
                             APERTE_START_TILE_X, APERTE_START_TILE_Y, FALSE, TRUE);
        else
            VDP_clearTileMapRect(BG_B, APERTE_START_TILE_X, APERTE_START_TILE_Y,
                                  APERTE_START_TILE_W, APERTE_START_TILE_H);
    }
}
