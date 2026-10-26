#ifndef UI_H
#define UI_H
#include "wl_types.h"
#include "gen/pics.h"

/* colour slots inside the per-screen 16 colour palette */
enum { K_BORD, K_BORD2, K_DEACT, K_BKGD, K_STRIPE, K_READ, K_READH, K_VIEW, K_TEXT, K_HL, K_BLACK, K_WHITE };
extern const u8 ui_kmenu[12], ui_kinter[12], ui_khs[12];
extern const u8 *K;

void ui_open(u16 group, const u8 *k);   /* fade out, 320x200 mode, black palette */
void ui_show(void);                     /* upload and fade in */
void ui_hide(void);                     /* fade out */
void ui_bar(s16 x, s16 y, s16 w, s16 h, u8 c);
void ui_clear(void);
void ui_stripes(s16 y);
void ui_window(s16 x, s16 y, s16 w, s16 h);
void ui_pic(s16 x, s16 y, u16 pic);
void ui_text(u16 font, s16 x, s16 y, const char *s, u8 color);
void ui_text_bg(u16 font, s16 x, s16 y, s16 w, const char *s, u8 color, u8 bg);
void ui_message(const char *str);
void ui_itoa(char *buf, s32 v);

void HelpScreens(void);
void EndText(void);
#endif
