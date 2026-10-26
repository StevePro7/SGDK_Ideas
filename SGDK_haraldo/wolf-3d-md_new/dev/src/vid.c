/* vid.c - Genesis video layer (see vid.h) */
#include <genesis.h>
#include <string.h>
#include "vid.h"
#include "snd.h"
#include "input.h"

u8 screenbuf[SCREEN_BYTES] __attribute__((aligned(4)));

Surface viewsurf, statsurf, fullsurf;

volatile u16 vid_front;
volatile u32 vid_frames;
volatile u32 TimeCount;
static u16 tickacc;
static u8 vmode;                /* 0 = game, 1 = full 320x200, 2 = split (160 + status bar) */
static boolean vid_pal;

u16 cur_pal[64];

/* ------------------------------------------------------------------ DMA */

#define MAXJOBS     64
#define JOB_FLIP    1
typedef struct
{
    const u8 *src;
    u16 dst;
    u16 len;
    u16 flags;
} DmaJob;

static DmaJob jobs[MAXJOBS];
static volatile u16 jhead, jtail;
volatile u32 vid_jdone;
static u32 jqueued;
u16 vid_target = 1;           /* view buffer being rendered into */
static u16 vblank_budget = 7000;

u32 vid_queue(const void *src, u16 dst, u16 len)
{
    u16 n;
    if (!len) return jqueued;
    for (;;)
    {
        n = (jhead + 1) % MAXJOBS;
        if (n != jtail) break;
        vid_frame();
    }
    jobs[jhead].src = src;
    jobs[jhead].dst = dst;
    jobs[jhead].len = len;
    jobs[jhead].flags = 0;
    jhead = n;
    return ++jqueued;
}

void vid_wait_job(u32 seq)
{
    while (vid_jdone < seq)
        vid_frame();
}

static void queue_flag(u16 flags)
{
    u16 n = (jhead + 1) % MAXJOBS;
    while (n == jtail) { vid_frame(); n = (jhead + 1) % MAXJOBS; }
    jobs[jhead].src = NULL;
    jobs[jhead].len = 0;
    jobs[jhead].dst = 0;
    jobs[jhead].flags = flags;
    jhead = n;
    jqueued++;
}

void vid_wait_idle(void)
{
    while (jhead != jtail)
        vid_frame();
}

static void do_flip(void)
{
    vid_front ^= 1;
    VDP_setVerticalScroll(BG_A, vid_front ? 256 : 0);
}

static void vint(void)
{
    u16 budget = vblank_budget;

    vid_frames++;
    tickacc += vid_pal ? 84 : 70;     /* TimeCount runs at 70 Hz */
    while (tickacc >= 60) { tickacc -= 60; TimeCount++; }

    if (jhead != jtail)
    {
        Z80_enableBusProtection();
        while (jhead != jtail && budget)
        {
            DmaJob *j = &jobs[jtail];
            if (j->flags & JOB_FLIP)
            {
                do_flip();
            }
            else
            {
                u16 n = j->len;
                if (n > budget) n = budget & ~1;
                if (!n) break;
                DMA_doDma(DMA_VRAM, (void *)j->src, j->dst, n >> 1, 2);
                j->src += n;
                j->dst += n;
                j->len -= n;
                budget -= n;
                if (j->len) break;
            }
            jtail = (jtail + 1) % MAXJOBS;
            vid_jdone++;
        }
        Z80_disableBusProtection();
    }
    JOY_update();
    in_latch |= JOY_readJoypad(JOY_1) & ~(BUTTON_UP | BUTTON_DOWN | BUTTON_LEFT | BUTTON_RIGHT);   /* D-pad is not latched: it would make movement coast */
    snd_tick();
}

/* ------------------------------------------------------------- surfaces */

static void surf_init(Surface *s, u8 *buf, u16 rows, u16 ncols, u16 tile)
{
    s->buf = buf;
    s->colbytes = rows * 4;
    s->ncols = ncols;
    s->vram = tile * 32;
    s->dirty = 0;
    s->dirty_hi = 0;
}

void surf_mark(Surface *s, s16 x, s16 w)
{
    s16 c0, c1, c;
    if (w <= 0) return;
    if (x < 0) { w += x; x = 0; }
    if (x + w > (s16)(s->ncols * 8)) w = s->ncols * 8 - x;
    if (w <= 0) return;
    c0 = x >> 3;
    c1 = (x + w - 1) >> 3;
    for (c = c0; c <= c1; c++)
    {
        if (c < 32) s->dirty |= 1ul << c;
        else s->dirty_hi |= 1 << (c - 32);
    }
}

void surf_markall(Surface *s)
{
    s->dirty = 0xFFFFFFFF;
    s->dirty_hi = 0xFF;
}

void vid_flush(Surface *s)
{
    u16 c = 0, start;
    u32 d = s->dirty;
    u8 dh = s->dirty_hi;
    u16 vram = s->vram;
    u16 n = s->ncols;
    if (s == &viewsurf)
        vram = vid_target ? TILE_VIEW1 * 32 : TILE_VIEW0 * 32;
    s->dirty = 0;
    s->dirty_hi = 0;
    while (c < n)
    {
        boolean set = (c < 32) ? (d >> c) & 1 : (dh >> (c - 32)) & 1;
        if (!set) { c++; continue; }
        start = c;
        while (c < n && ((c < 32) ? (d >> c) & 1 : (dh >> (c - 32)) & 1))
            c++;
        vid_queue(s->buf + start * s->colbytes, vram + start * s->colbytes,
            (c - start) * s->colbytes);
    }
}

void vid_flip_queue(void)
{
    queue_flag(JOB_FLIP);
    vid_target ^= 1;
}

void vid_present_view(void)
{
    vid_queue(viewsurf.buf, vid_target ? TILE_VIEW1 * 32 : TILE_VIEW0 * 32, VIEW_BYTES);
    viewsurf.dirty = 0;
    viewsurf.dirty_hi = 0;
    vid_flip_queue();
}

void vid_update(void)
{
    if (vmode == 1)
        vid_flush(&fullsurf);
    else if (vmode == 2)
    {
        vid_flush(&fullsurf);
        vid_flush(&statsurf);
    }
    else
    {
        vid_flush(&statsurf);
        vid_flush(&viewsurf);
    }
    vid_wait_idle();
}

/* --------------------------------------------------------------- setup */

static void map_rows(u8 mode)
{
    vu32 *ctrl = (vu32 *)VDP_CTRL_PORT;
    vu16 *data = (vu16 *)VDP_DATA_PORT;
    u16 x, y;
    SYS_disableInts();
    for (y = 0; y < 64; y++)
    {
        u16 yy = y & 31;
        *ctrl = VDP_WRITE_VRAM_ADDR(PLANE_ADDR + y * 128);
        for (x = 0; x < 64; x++)
        {
            u16 v = 0;
            if (x < 40)
            {
                if (mode == 1)
                {
                    if (yy < 25)
                        v = TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 1 + x * 25 + yy);
                }
                else if (mode == 2)
                {
                    if (yy < 20)
                        v = TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, 1 + x * 20 + yy);
                    else if (yy < 25)
                        v = TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, TILE_STATUS + x * STAT_ROWS + (yy - 20));
                }
                else if (yy < 28)
                {
                    if (x >= VIEW_CX0 && x < VIEW_CX0 + VIEWC &&
                        yy >= VIEW_CY0 && yy < VIEW_CY0 + VIEWR)
                        v = TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE,
                            (y < 32 ? TILE_VIEW0 : TILE_VIEW1) + (x - VIEW_CX0) * VIEWR + (yy - VIEW_CY0));
                    else if (yy >= STAT_CY0)
                        v = TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE,
                            TILE_STATUS + x * STAT_ROWS + (yy - STAT_CY0));
                    else
                        v = TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, TILE_BORDER);
                }
            }
            *data = v;
        }
    }
    SYS_enableInts();
    VDP_setVerticalScroll(BG_A, mode ? ((1024 - 12) & 0x3FF) : (vid_front ? 256 : 0));
}

void vid_init(void)
{
    u32 t[8];
    u16 i;
    vid_pal = IS_PAL_SYSTEM;
    SYS_setVIntCallback(vint);
    SYS_disableInts();
    VDP_setEnable(FALSE);
    VDP_setScreenWidth320();
    VDP_setScreenHeight224();
    VDP_setPlaneSize(64, 64, FALSE);
    VDP_setBGAAddress(PLANE_ADDR);
    /* plane B is never used: point it at a zeroed area so that colour 0 pixels of
       plane A (which are transparent) do not show a second, differently scrolled copy */
    VDP_setBGBAddress(0xC000);
    /* the sprite attribute table also goes there: sprites are never used, and the SGDK default
       location (0xF400) lies inside our tile data, which showed up as a stray 8x8 sprite */
    VDP_setSpriteListAddress(0xC000);
    {
        vu32 *ctrl = (vu32 *)VDP_CTRL_PORT;
        vu16 *data = (vu16 *)VDP_DATA_PORT;
        u16 i;
        *ctrl = VDP_WRITE_VRAM_ADDR(0xC000);
        for (i = 0; i < 0x1400 / 2; i++)
            *data = 0;
    }
    VDP_setWindowAddress(PLANE_ADDR);
    VDP_setHScrollTableAddress(HSCROLL_ADDR);
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);
    VDP_setWindowHPos(FALSE, 0);
    VDP_setWindowVPos(FALSE, 0);
    SYS_enableInts();
    VDP_setHorizontalScroll(BG_A, 0);
    VDP_setVerticalScroll(BG_A, 0);
    VDP_setHorizontalScroll(BG_B, 0);
    VDP_setVerticalScroll(BG_B, 0);

    /* border tile: every pixel uses colour 1 */
    for (i = 0; i < 8; i++) t[i] = 0x11111111;
    VDP_loadTileData(t, TILE_BORDER, 1, CPU);

    surf_init(&viewsurf, screenbuf, VIEWH, VIEWC, TILE_VIEW0);
    surf_init(&statsurf, screenbuf + VIEW_BYTES, 40, STAT_COLS, TILE_STATUS);
    surf_init(&fullsurf, screenbuf, 200, 40, 1);
    vmode = 0;
    vid_front = 0;
    memset(cur_pal, 0, sizeof(cur_pal));
    PAL_setColors(0, cur_pal, 64, CPU);
}

void vid_game_mode(void)
{
    vid_wait_idle();
    vmode = 0;
    vid_front = 0;
    vid_target = 1;
    surf_init(&statsurf, screenbuf + VIEW_BYTES, 40, STAT_COLS, TILE_STATUS);
    VDP_setEnable(FALSE);
    map_rows(0);
    memset(screenbuf, 0, SCREEN_BYTES);
    surf_markall(&statsurf);
    surf_markall(&viewsurf);
    vid_flush(&statsurf);
    vid_flush(&viewsurf);
    vid_wait_idle();
    VDP_setEnable(TRUE);
}

void vid_full_mode(void)
{
    vid_wait_idle();
    vmode = 1;
    surf_init(&fullsurf, screenbuf, 200, 40, 1);
    VDP_setEnable(FALSE);
    map_rows(1);
    memset(screenbuf, 0, SCREEN_BYTES);
    surf_markall(&fullsurf);
    vid_flush(&fullsurf);
    vid_wait_idle();
    VDP_setEnable(TRUE);
}

/* 320x160 picture area on top of the 40 pixel status bar (intermission) */
void vid_split_mode(void)
{
    vid_wait_idle();
    vmode = 2;
    surf_init(&fullsurf, screenbuf, 160, 40, 1);
    surf_init(&statsurf, screenbuf + 25600, 40, STAT_COLS, TILE_STATUS);
    VDP_setEnable(FALSE);
    map_rows(2);
    memset(screenbuf, 0, SCREEN_BYTES);
    surf_markall(&fullsurf);
    surf_markall(&statsurf);
    vid_flush(&fullsurf);
    vid_flush(&statsurf);
    vid_wait_idle();
    VDP_setEnable(TRUE);
}

boolean vid_isfull(void)
{
    return vmode != 0;
}

/* ---------------------------------------------------------------- waits */

void vid_frame(void)
{
    u32 f = vid_frames;
    while (vid_frames == f)
        ;
}

void vid_wait(u16 n)
{
    while (n--)
        vid_frame();
}

/* ------------------------------------------------------------- palette */

void vid_set_pal(u16 line, const u16 *pal)
{
    memcpy(&cur_pal[line * 16], pal, 32);
    PAL_setColors(line * 16, pal, 16, CPU);
}

void vid_set_backdrop(u16 color)
{
    VDP_setBackgroundColor(0);
    PAL_setColor(0, color);
}

void vid_black(void)
{
    static const u16 z[64];
    memset(cur_pal, 0, sizeof(cur_pal));
    PAL_setColors(0, z, 64, CPU);
}

static u16 lerp_col(u16 a, u16 b, u16 t, u16 n)
{
    s16 ar = (a >> 1) & 7, ag = (a >> 5) & 7, ab = (a >> 9) & 7;
    s16 br = (b >> 1) & 7, bg = (b >> 5) & 7, bb = (b >> 9) & 7;
    s16 r = ar + ((br - ar) * (s16)t) / (s16)n;
    s16 g = ag + ((bg - ag) * (s16)t) / (s16)n;
    s16 bl = ab + ((bb - ab) * (s16)t) / (s16)n;
    return (bl << 9) | (g << 5) | (r << 1);
}

/* crossfade the live palette towards the three given lines (NULL = black) */
void vid_fade_to(const u16 *p0, const u16 *p1, const u16 *p2, u16 frames)
{
    static const u16 z[16];
    u16 from[48], to[48], cur[48];
    u16 f, i;
    if (!p0) p0 = z;
    if (!p1) p1 = z;
    if (!p2) p2 = z;
    memcpy(from, cur_pal, 96);
    memcpy(to, p0, 32);
    memcpy(to + 16, p1, 32);
    memcpy(to + 32, p2, 32);
    for (f = 1; f <= frames; f++)
    {
        for (i = 0; i < 48; i++)
            cur[i] = lerp_col(from[i], to[i], f, frames);
        vid_frame();
        PAL_setColors(0, cur, 48, CPU);
    }
    memcpy(cur_pal, to, 96);
    PAL_setColors(0, to, 48, CPU);
}

void vid_fade_out(u16 frames)
{
    vid_fade_to(NULL, NULL, NULL, frames);
}

/* blend the palette toward (r,g,b) (each 0..7) by level/levels */
void vid_tint(const u16 *base, u16 *out, s16 r, s16 g, s16 b, u16 level, u16 levels)
{
    u16 i;
    u16 tgt = (b << 9) | (g << 5) | (r << 1);
    for (i = 0; i < 16; i++)
        out[i] = lerp_col(base[i], tgt, level, levels);
}
