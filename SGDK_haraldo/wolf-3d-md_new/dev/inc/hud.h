#ifndef HUD_H
#define HUD_H
#include "wl_types.h"
void StatusDrawPic(u16 x, u16 y, u16 picnum);   /* x in 8 pixel units, y in pixels */
void HUD_Init(void);
extern u16 game_pal1[16];
#endif
