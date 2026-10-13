#include <genesis.h>
#include "title.h"
#include "resources.h"

static u16 blink_timer;
static u16 start_visible;

void title_init(void)
{
    VDP_setScreenWidth320();

    PAL_setPalette(PAL0, title_bg.palette->data, DMA);
    PAL_setPalette(PAL1, heloisa_img.palette->data, DMA);

    VDP_drawImageEx(BG_B, &title_bg, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USER_INDEX), 0, 0, FALSE, TRUE);

    u16 heloisa_tile_index = TILE_USER_INDEX + title_bg.tileset->numTile;
    VDP_drawImageEx(BG_A, &heloisa_img, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, heloisa_tile_index), 10, 3, FALSE, TRUE);

    VDP_setTextPalette(PAL0);
    VDP_setTextPlane(BG_A);

    blink_timer = 0;
    start_visible = TRUE;
}

void title_update(void)
{
    blink_timer++;

    if (blink_timer >= 30)
    {
        blink_timer = 0;
        start_visible = !start_visible;

        if (start_visible)
            VDP_drawText("APERTE START", 12, 25);
        else
            VDP_clearTextArea(12, 25, 16, 1);
    }
}
