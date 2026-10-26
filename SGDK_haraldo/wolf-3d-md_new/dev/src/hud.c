/* hud.c - status bar drawing */
#include "wl_def.h"
#include "pic.h"
#include "hud.h"
#include <string.h>

u16 game_pal1[16];

void HUD_Init(void)
{
    memcpy(game_pal1, pic_group_pal[PG_HUD], 32);
}

void StatusDrawPic(u16 x, u16 y, u16 picnum)
{
    pic_draw(&statsurf, x * 8, y, picnum);
}
