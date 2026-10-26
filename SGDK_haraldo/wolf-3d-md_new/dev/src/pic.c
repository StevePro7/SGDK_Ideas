/* pic.c - blitting of converted pictures and bitmap fonts into the 4bpp surfaces */
#include <genesis.h>
#include <string.h>
#include "pic.h"

void pic_size(u16 picnum, u16 *w, u16 *h)
{
    const pic_t *p = &pic_tab[picnum - PIC_FIRST];
    *w = p->w8 * 8;
    *h = p->h;
}

const u16 *pic_pal(u16 picnum)
{
    return pic_group_pal[pic_tab[picnum - PIC_FIRST].group];
}

void pic_draw(Surface *s, s16 x, s16 y, u16 picnum)
{
    const pic_t *p = &pic_tab[picnum - PIC_FIRST];
    const u8 *src = pic_data + p->ofs;
    u16 cx, rows = s->colbytes >> 2;
    u16 colbytes = p->h * 4;
    u16 c0 = x >> 3;
    s16 h = p->h;
    u16 n = colbytes;
    if (y >= (s16)rows) return;
    if (y + h > (s16)rows) { h = rows - y; n = h * 4; }
    for (cx = 0; cx < p->w8; cx++)
    {
        if (c0 + cx < s->ncols)
            memcpy(s->buf + (c0 + cx) * s->colbytes + y * 4, src + cx * colbytes, n);
    }
    surf_mark(s, x, p->w8 * 8);
}

void pic_pixel(Surface *s, s16 x, s16 y, u8 color)
{
    u8 *b;
    if ((u16)x >= s->ncols * 8 || (u16)y >= (s->colbytes >> 2)) return;
    b = s->buf + (x >> 3) * s->colbytes + y * 4 + ((x & 7) >> 1);
    if (x & 1) *b = (*b & 0xF0) | color;
    else *b = (*b & 0x0F) | (color << 4);
}

void pic_fill(Surface *s, s16 x, s16 y, s16 w, s16 h, u8 color)
{
    s16 i, j;
    u8 pair = (color << 4) | color;
    s16 x1 = x + w, y1 = y + h;
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x1 > (s16)(s->ncols * 8)) x1 = s->ncols * 8;
    if (y1 > (s16)(s->colbytes >> 2)) y1 = s->colbytes >> 2;
    if (x1 <= x || y1 <= y) return;
    for (i = x; i < x1; i++)
    {
        if (!(i & 1) && i + 1 < x1)
        {
            u8 *b = s->buf + (i >> 3) * s->colbytes + y * 4 + ((i & 7) >> 1);
            for (j = y; j < y1; j++, b += 4) *b = pair;
            i++;
        }
        else
            for (j = y; j < y1; j++) pic_pixel(s, i, j, color);
    }
    surf_mark(s, x, x1 - x);
}

s16 txt_width(u16 font, const char *str)
{
    s16 w = 0;
    while (*str) w += fonts[font].width[(u8)*str++];
    return w;
}

void txt_height(u16 font, u16 *h)
{
    *h = fonts[font].height;
}

void txt_draw(Surface *s, u16 font, s16 x, s16 y, const char *str, u8 color)
{
    const font_t *f = &fonts[font];
    s16 x0 = x;
    while (*str)
    {
        u8 ch = *str++;
        u16 w = f->width[ch], r, b;
        const u16 *g = f->data + f->loc[ch];
        for (r = 0; r < f->height; r++)
        {
            u16 bits = g[r];
            for (b = 0; b < w && bits; b++, bits <<= 1)
                if (bits & 0x8000)
                    pic_pixel(s, x + b, y + r, color);
        }
        x += w;
    }
    surf_mark(s, x0, x - x0);
}
