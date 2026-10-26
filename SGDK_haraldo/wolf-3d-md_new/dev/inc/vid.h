/* vid.h - Genesis video layer for the Wolfenstein 3D port.
 *
 * The 3-D view and the status bar are 4bpp RAM bitmaps stored in the VDP
 * tile layout (column-major: one "tile column" = rows*4 bytes) and copied to
 * VRAM by DMA from the vertical-blank interrupt.  The view is double
 * buffered in VRAM (plane rows 0-31 map buffer 0, rows 32-63 buffer 1) so a
 * page flip is a single vertical scroll write.
 */
#ifndef VID_H
#define VID_H

#include "wl_types.h"
#include "gen/gen.h"

#define VIEWC           (VIEWW / 8)             /* view tile columns */
#define VIEWR           (VIEWH / 8)             /* view tile rows    */
#define VIEW_TILES      (VIEWC * VIEWR)
#define VIEW_COLBYTES   (VIEWR * 32)            /* bytes per view tile column */
#define VIEW_BYTES      (VIEW_TILES * 32)
#define STAT_COLS       40
#define STAT_ROWS       5
#define STAT_COLBYTES   (STAT_ROWS * 32)
#define STAT_BYTES      (STAT_COLS * STAT_COLBYTES)
#define SCREEN_BYTES    32000

#define TILE_VIEW0      1
#define TILE_VIEW1      (TILE_VIEW0 + VIEW_TILES)
#define TILE_STATUS     (TILE_VIEW1 + VIEW_TILES)
#define TILE_BORDER     (TILE_STATUS + STAT_COLS * STAT_ROWS)
#define PLANE_ADDR      0xE000
#define HSCROLL_ADDR    0xD400

#define VIEW_CX0        ((40 - VIEWC) / 2)      /* plane cell of the view */
#define VIEW_CY0        ((23 - VIEWR) / 2)
#define STAT_CY0        23

typedef struct
{
    u8 *buf;
    u16 colbytes;       /* bytes per 8 pixel tile column */
    u16 ncols;
    u16 vram;           /* VRAM byte address of tile column 0 */
    u32 dirty;          /* one bit per tile column needing upload */
    u8 dirty_hi;
} Surface;

extern u8 screenbuf[SCREEN_BYTES];
extern Surface viewsurf, statsurf, fullsurf;

extern volatile u16 vid_front;
extern volatile u32 vid_frames;
extern volatile u32 TimeCount;          /* 70 Hz */

void vid_init(void);                    /* one time VDP setup + V-Int */
void vid_game_mode(void);               /* 3-D view + status bar layout */
void vid_full_mode(void);               /* 320x200 2-D surface */
void vid_split_mode(void);              /* 320x160 surface + status bar */
boolean vid_isfull(void);

u32 vid_queue(const void *src, u16 vramdst, u16 len);
void vid_wait_job(u32 seq);
void vid_flip_queue(void);
extern u16 vid_target;
void vid_wait_idle(void);
void vid_frame(void);
void vid_wait(u16 frames);

void surf_mark(Surface *s, s16 x, s16 w);
void surf_markall(Surface *s);
void vid_flush(Surface *s);
void vid_present_view(void);            /* queue whole view to back buffer + flip */
void vid_update(void);                  /* flush surfaces and wait */

/* palettes: 0 = 3-D view, 1 = status bar, 2 = border/overlay */
void vid_set_pal(u16 line, const u16 *pal);
void vid_black(void);
void vid_fade_to(const u16 *pal0, const u16 *pal1, const u16 *pal2, u16 frames);
void vid_fade_out(u16 frames);
void vid_set_backdrop(u16 color);
void vid_tint(const u16 *base, u16 *out, s16 r, s16 g, s16 b, u16 level, u16 levels);

#endif
