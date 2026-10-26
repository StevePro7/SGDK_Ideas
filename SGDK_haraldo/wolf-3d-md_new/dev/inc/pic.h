/* pic.h - 2-D pictures and fonts (converted from VGAGRAPH) */
#ifndef PIC_H
#define PIC_H
#include "wl_types.h"
#include "vid.h"
#include "gen/pics.h"

void pic_draw(Surface *s, s16 x, s16 y, u16 picnum);        /* x multiple of 8 */
void pic_size(u16 picnum, u16 *w, u16 *h);
const u16 *pic_pal(u16 picnum);
void pic_fill(Surface *s, s16 x, s16 y, s16 w, s16 h, u8 color);
void pic_pixel(Surface *s, s16 x, s16 y, u8 color);
s16  txt_width(u16 font, const char *str);
void txt_draw(Surface *s, u16 font, s16 x, s16 y, const char *str, u8 color);
void txt_height(u16 font, u16 *h);
#endif
