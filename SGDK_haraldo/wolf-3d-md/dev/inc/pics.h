#ifndef PICS_H
#define PICS_H
#include "wl_types.h"
typedef struct { u16 w8; u16 h; u16 group; u32 ofs; } pic_t;
extern const u8 pic_data[];
extern const pic_t pic_tab[144];
extern const u16 border_color;
extern const u16 pic_group_pal[9][16];
#define PG_HUD 0
#define PG_MENU 1
#define PG_INTER 2
#define PG_TITLE 3
#define PG_PG13 4
#define PG_CREDITS 5
#define PG_HSCORE 6
#define PG_HELP 7
#define PG_VIEW 8
#define PC_MENU_BORD 0
#define PC_MENU_BORD2 1
#define PC_MENU_DEACTIVE 2
#define PC_MENU_BKGD 3
#define PC_MENU_STRIPE 2
#define PC_MENU_READ 4
#define PC_MENU_READH 5
#define PC_MENU_VIEW 6
#define PC_MENU_TEXT 7
#define PC_MENU_HIGHLIGHT 8
#define PC_MENU_BLACK 9
#define PC_MENU_WHITE 10
#define PC_INTER_BORD 0
#define PC_INTER_BORD2 1
#define PC_INTER_DEACTIVE 2
#define PC_INTER_BKGD 3
#define PC_INTER_STRIPE 2
#define PC_INTER_READ 4
#define PC_INTER_READH 5
#define PC_INTER_VIEW 6
#define PC_INTER_TEXT 7
#define PC_INTER_HIGHLIGHT 8
#define PC_INTER_BLACK 9
#define PC_INTER_WHITE 10
#define PC_HSCORE_BORD 0
#define PC_HSCORE_BORD2 1
#define PC_HSCORE_DEACTIVE 2
#define PC_HSCORE_BKGD 3
#define PC_HSCORE_STRIPE 2
#define PC_HSCORE_READ 4
#define PC_HSCORE_READH 5
#define PC_HSCORE_VIEW 6
#define PC_HSCORE_TEXT 7
#define PC_HSCORE_HIGHLIGHT 8
#define PC_HSCORE_BLACK 9
#define PC_HSCORE_WHITE 10
#define HELP_NCOLORS 11
extern const u8 help_cmap[HELP_NCOLORS][2];
#define PIC_FIRST 3
typedef struct { u16 height; u16 loc[256]; u8 width[256]; const u16 *data; } font_t;
extern const font_t fonts[2];
#endif
