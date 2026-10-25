/* ui.c - control panel (port of WL_MENU.C), help text engine (WL_TEXT.C) and shared 2-D screen helpers */
#include "wl_def.h"
#include "snd.h"
#include "vid.h"
#include "pic.h"
#include "input.h"
#include "hud.h"
#include "menu.h"
#include "inter.h"
#include "ui.h"
#include "save.h"
#include <string.h>

extern const char help_text[];
extern const char end_text[];

/* ------------------------------------------------------------ colours */

#define KTAB(G) { PC_##G##_BORD, PC_##G##_BORD2, PC_##G##_DEACTIVE, PC_##G##_BKGD, PC_##G##_STRIPE, \
                  PC_##G##_READ, PC_##G##_READH, PC_##G##_VIEW, PC_##G##_TEXT, PC_##G##_HIGHLIGHT, \
                  PC_##G##_BLACK, PC_##G##_WHITE }
const u8 ui_kmenu[12] = KTAB(MENU);
const u8 ui_kinter[12] = KTAB(INTER);
const u8 ui_khs[12] = KTAB(HSCORE);

const u8 *K = ui_kmenu;
static u16 ui_group;

#define SF (&fullsurf)

/* --------------------------------------------------- screen management */

void ui_open(u16 group, const u8 *k)
{
    vid_fade_out(6);
    vid_full_mode();
    vid_black();
    K = k;
    ui_group = group;
}

void ui_show(void)
{
    vid_update();
    vid_fade_to(pic_group_pal[ui_group], NULL, NULL, 10);
}

void ui_hide(void)
{
    vid_fade_out(10);
}

void ui_bar(s16 x, s16 y, s16 w, s16 h, u8 c)
{
    pic_fill(SF, x, y, w, h, c);
}

void ui_clear(void)
{
    ui_bar(0, 0, 320, 200, K[K_BORD]);
}

void ui_stripes(s16 y)
{
    ui_bar(0, y, 320, 24, K[K_BLACK]);
    ui_bar(0, y + 22, 320, 1, K[K_STRIPE]);
}

static void outline(s16 x, s16 y, s16 w, s16 h, u8 c1, u8 c2)
{
    ui_bar(x, y, w + 1, 1, c2);
    ui_bar(x, y, 1, h + 1, c2);
    ui_bar(x, y + h, w + 1, 1, c1);
    ui_bar(x + w, y, 1, h + 1, c1);
}

void ui_window(s16 x, s16 y, s16 w, s16 h)
{
    ui_bar(x, y, w, h, K[K_BKGD]);
    outline(x, y, w, h, K[K_BORD2], K[K_DEACT]);
}

static void drawpic(s16 x, s16 y, u16 pic)
{
    pic_draw(SF, x, y, pic);
}

void ui_pic(s16 x, s16 y, u16 pic)
{
    drawpic(x, y, pic);
}

void ui_text(u16 font, s16 x, s16 y, const char *s, u8 color)
{
    txt_draw(SF, font, x, y, s, color);
}

/* print a string with a solid background box behind it */
void ui_text_bg(u16 font, s16 x, s16 y, s16 w, const char *s, u8 color, u8 bg)
{
    u16 h;
    txt_height(font, &h);
    ui_bar(x, y, w, h, bg);
    txt_draw(SF, font, x, y, s, color);
}

static void ntoa(char *buf, s32 v)
{
    char t[12];
    s16 n = 0, i = 0;
    if (v < 0) { buf[i++] = '-'; v = -v; }
    if (v == 0) t[n++] = '0';
    while (v) { t[n++] = '0' + (v % 10); v /= 10; }
    while (n) buf[i++] = t[--n];
    buf[i] = 0;
}

void ui_itoa(char *buf, s32 v)
{
    ntoa(buf, v);
}

/* ------------------------------------------------------------ messages */

/* centred window with some lines of text, font 1 */
void ui_message(const char *str)
{
    u16 fh;
    s16 w = 0, lines = 1, y, x, i;
    const char *p;
    char line[48];
    txt_height(1, &fh);
    for (p = str; *p; p++)
        if (*p == '\n') lines++;
    p = str;
    while (*p)
    {
        s16 n = 0;
        while (*p && *p != '\n') line[n++] = *p++;
        line[n] = 0;
        if (*p) p++;
        i = txt_width(1, line);
        if (i > w) w = i;
    }
    w += 12;
    x = 160 - w / 2;
    y = 100 - (lines * fh) / 2 - 6;
    ui_bar(x - 2, y - 2, w + 4, lines * fh + 16, K[K_BORD2]);
    ui_window(x, y, w, lines * fh + 12);
    p = str;
    i = 0;
    while (*p)
    {
        s16 n = 0;
        while (*p && *p != '\n') line[n++] = *p++;
        line[n] = 0;
        if (*p) p++;
        ui_text(1, 160 - txt_width(1, line) / 2, y + 6 + i * fh, line, K[K_READH]);
        i++;
    }
    vid_update();
}

static boolean ui_confirm(const char *str)
{
    boolean r;
    ui_message(str);
    IN_ClearKeys();
    for (;;)
    {
        vid_frame();
        IN_Update();
        if (in_pressed & (BUTTON_A | BUTTON_C | BUTTON_START)) { r = TRUE; break; }
        if (in_pressed & BUTTON_B) { r = FALSE; break; }
    }
    SD_PlaySound(r ? SHOOTSND : ESCPRESSEDSND);
    return r;
}

/* --------------------------------------------------------- menu engine */

typedef struct { const char *s; u8 active; } mitem_t;
typedef struct { s16 x, y; u8 amount; s8 curpos; s16 indent; s16 erasew; } minfo_t;

static u8 item_color(u8 active, boolean hl)
{
    switch (active)
    {
    case 0: return K[K_BORD];
    case 2: return hl ? K[K_HL] : K[K_READH];
    default: return hl ? K[K_HL] : K[K_TEXT];
    }
}

static void draw_item(const minfo_t *mi, const mitem_t *it, s16 i, boolean hl)
{
    s16 y = mi->y + i * 13;
    s16 x = mi->x + mi->indent;
    if (!it[i].s[0]) return;
    ui_bar(x - 1, y, mi->erasew, 13, K[K_BKGD]);
    ui_text(1, x, y, it[i].s, item_color(it[i].active, hl));
}

static void draw_menu(const minfo_t *mi, const mitem_t *it)
{
    s16 i;
    for (i = 0; i < mi->amount; i++)
        draw_item(mi, it, i, i == mi->curpos);
}

static void draw_gun(const minfo_t *mi, s16 which, boolean anim)
{
    s16 x = mi->x & ~7;
    s16 y = mi->y + which * 13 - 2;
    drawpic(x, y, anim ? C_CURSOR2PIC : C_CURSOR1PIC);
}

/* draw all items and the cursor (call before the screen is faded in) */
static void menu_prepare(minfo_t *mi, mitem_t *it, void (*routine)(s16))
{
    s16 which = mi->curpos, i;
    s16 x = mi->x & ~7;
    for (i = 0; i < mi->amount && !it[which].active; i++)
        which = (which + 1) % mi->amount;
    mi->curpos = which;
    draw_menu(mi, it);
    ui_bar(x - 1, mi->y - 2, 25, mi->amount * 13 + 2, K[K_BKGD]);
    draw_gun(mi, which, 0);
    if (routine) routine(which);
}

/* returns the chosen item, or -1 when B / Start backs out */
static s16 handle_menu(minfo_t *mi, mitem_t *it, void (*routine)(s16))
{
    s16 which = mi->curpos, i;
    u8 anim = 0;
    u16 t = 0, hold = 0;
    s16 x = mi->x & ~7;

    IN_ClearKeys();
    for (;;)
    {
        s16 dir = 0;
        vid_frame();
        IN_Update();
        t++;
        if ((t & 7) == 0)
        {
            anim ^= 1;
            draw_gun(mi, which, anim);
            vid_update();
        }
        if (in_pressed & (BUTTON_UP | BUTTON_DOWN)) { hold = 0; dir = (in_pressed & BUTTON_UP) ? -1 : 1; }
        else if (in_held & (BUTTON_UP | BUTTON_DOWN))
        {
            hold++;
            if (hold > 18 && ((hold - 18) & 3) == 0)
                dir = (in_held & BUTTON_UP) ? -1 : 1;
        }
        else hold = 0;
        if (dir)
        {
            s16 n = which;
            ui_bar(x - 1, mi->y + which * 13 - 2, 25, 18, K[K_BKGD]);
            draw_item(mi, it, which, FALSE);
            for (i = 0; i < mi->amount; i++)
            {
                n += dir;
                if (n < 0) n = mi->amount - 1;
                if (n >= mi->amount) n = 0;
                if (it[n].active) break;
            }
            which = n;
            draw_item(mi, it, which, TRUE);
            draw_gun(mi, which, anim);
            if (routine) routine(which);
            vid_update();
            SD_PlaySound(MOVEGUN2SND);
        }
        if (in_pressed & (BUTTON_A | BUTTON_C | BUTTON_START))
        {
            mi->curpos = which;
            SD_PlaySound(SHOOTSND);
            return which;
        }
        if (in_pressed & BUTTON_B)
        {
            mi->curpos = which;
            SD_PlaySound(ESCPRESSEDSND);
            return -1;
        }
    }
}

/* ---------------------------------------------------------- main menu */

#define MENU_X  76
#define MENU_Y  55
#define MENU_W  178

enum { M_NEW, M_SOUND, M_CONTROL, M_LOAD, M_SAVE, M_READ, M_SCORES, M_BACK, M_COUNT };

static mitem_t MainMenu[M_COUNT] =
{
    {"New Game", 1},
    {"Sound", 1},
    {"Control", 1},
    {"Load Game", 1},
    {"Save Game", 0},
    {"Read This!", 2},
    {"View Scores", 1},
    {"Back to Demo", 1},
};
static minfo_t MainItems = { MENU_X, MENU_Y, M_COUNT, 0, 24, 140 };

boolean ingame;
s16 newgame_difficulty;

static void draw_main_menu(void)
{
    ui_clear();
    drawpic(112, 184, C_MOUSELBACKPIC);
    ui_stripes(10);
    drawpic(84, 0, C_OPTIONSPIC);
    ui_window(MENU_X - 8, MENU_Y - 3, MENU_W, 13 * M_COUNT + 6);
    MainMenu[M_BACK].s = ingame ? "Back to Game" : "Back to Demo";
    MainMenu[M_SAVE].active = ingame ? 1 : 0;
}

/* ------------------------------------------------------------ new game */

#define NM_X    50
#define NM_Y    100
#define NM_W    225
#define NM_H    (13 * 4 + 15)

static mitem_t NewMenu[4] =
{
    {"Can I play, Daddy?", 1},
    {"Don't hurt me.", 1},
    {"Bring 'em on!", 1},
    {"I am Death incarnate!", 1},
};
static minfo_t NewItems = { NM_X, NM_Y, 4, 2, 24, 190 };

static void new_game_face(s16 w)
{
    ui_bar(NM_X + 185, NM_Y + 7, 24, 32, K[K_BKGD]);
    drawpic(NM_X + 185, NM_Y + 7, C_BABYMODEPIC + w);
}

static void draw_new_game(void)
{
    ui_clear();
    drawpic(112, 184, C_MOUSELBACKPIC);
    ui_text(1, NM_X + 20, NM_Y - 32, "How tough are you?", K[K_READH]);
    ui_window(NM_X - 5, NM_Y - 10, NM_W, NM_H);
}

static boolean cp_new_game(void)
{
    s16 which;
    ui_open(PG_MENU, ui_kmenu);
    draw_new_game();
    if (ingame)
    {
        ui_show();
        if (!ui_confirm("You are currently in a game.\nContinuing will erase\nold game.  Ok?  (A/B)"))
            return FALSE;
        draw_new_game();
        menu_prepare(&NewItems, NewMenu, new_game_face);
        vid_update();
    }
    else
    {
        menu_prepare(&NewItems, NewMenu, new_game_face);
        ui_show();
    }
    which = handle_menu(&NewItems, NewMenu, new_game_face);
    if (which < 0)
        return FALSE;
    newgame_difficulty = which;
    NewGame(which, 0);
    startgame = TRUE;
    return TRUE;
}

/* --------------------------------------------------------------- sound */

#define SM_X    48
#define SM_W    250
#define SM_Y1   20
#define SM_H1   (4 * 13 - 7)
#define SM_Y2   (SM_Y1 + 5 * 13)
#define SM_H2   (4 * 13 - 7)
#define SM_Y3   (SM_Y2 + 5 * 13)
#define SM_H3   (3 * 13 - 7)

static mitem_t SndMenu[12] =
{
    {"None", 1}, {"PC Speaker", 0}, {"AdLib / YM2612", 1}, {"", 0}, {"", 0},
    {"None", 1}, {"Disney Sound Source", 0}, {"Sound Blaster / PCM", 1}, {"", 0}, {"", 0},
    {"None", 1}, {"AdLib / YM2612", 1},
};
static minfo_t SndItems = { SM_X, SM_Y1, 12, 0, 52, 190 };

static void draw_sound_menu(void)
{
    s16 i;
    ui_clear();
    drawpic(112, 184, C_MOUSELBACKPIC);
    ui_window(SM_X - 8, SM_Y1 - 3, SM_W, SM_H1);
    ui_window(SM_X - 8, SM_Y2 - 3, SM_W, SM_H2);
    ui_window(SM_X - 8, SM_Y3 - 3, SM_W, SM_H3);
    drawpic(100, SM_Y1 - 20, C_FXTITLEPIC);
    drawpic(100, SM_Y2 - 20, C_DIGITITLEPIC);
    drawpic(100, SM_Y3 - 20, C_MUSICTITLEPIC);
    for (i = 0; i < 12; i++)
    {
        boolean on = FALSE;
        if (!SndMenu[i].s[0]) continue;
        switch (i)
        {
        case 0: on = !SoundOn; break;
        case 2: on = SoundOn; break;
        case 5: on = DigiMode == sds_Off; break;
        case 7: on = DigiMode == sds_SoundBlaster; break;
        case 10: on = !MusicOn; break;
        case 11: on = MusicOn; break;
        }
        drawpic(SM_X + 24, SM_Y1 + i * 13 + 2, on ? C_SELECTEDPIC : C_NOTSELECTEDPIC);
    }
}

static void cp_sound(void)
{
    s16 which;
    ui_open(PG_MENU, ui_kmenu);
    draw_sound_menu();
    menu_prepare(&SndItems, SndMenu, NULL);
    ui_show();
    for (;;)
    {
        which = handle_menu(&SndItems, SndMenu, NULL);
        switch (which)
        {
        case 0: SoundOn = FALSE; SD_StopSound(); break;
        case 2: SoundOn = TRUE; SD_PlaySound(SHOOTSND); break;
        case 5: DigiMode = sds_Off; SD_StopSound(); break;
        case 7: DigiMode = sds_SoundBlaster; SD_PlaySound(SHOOTSND); break;
        case 10: if (MusicOn) { MusicOn = FALSE; SD_MusicOff(); } break;
        case 11: if (!MusicOn) { MusicOn = TRUE; SD_StartMusic(WONDERIN_MUS); } break;
        default: break;
        }
        if (which < 0)
            return;
        draw_sound_menu();
        menu_prepare(&SndItems, SndMenu, NULL);
        vid_update();
    }
}

/* ------------------------------------------------------------- control */

#define CTL_X   24
#define CTL_Y   70
#define CTL_W   284

static const char *const ctl_lines[][2] =
{
    { "D-Pad", "Move and turn" },
    { "B", "Fire weapon" },
    { "A (hold)", "Run" },
    { "C", "Use: doors, switches, walls" },
    { "C + Left/Right", "Strafe" },
    { "A + C", "Next weapon" },
    { "X / Y / Z", "Knife / Pistol / Machine gun" },
    { "Start", "Menu" },
};

static void cp_control(void)
{
    s16 i;
    ui_open(PG_MENU, ui_kmenu);
    ui_clear();
    ui_stripes(10);
    drawpic(80, 0, C_CONTROLPIC);
    drawpic(112, 184, C_MOUSELBACKPIC);
    ui_window(CTL_X - 8, CTL_Y - 21, CTL_W, 13 * 8 + 12);
    for (i = 0; i < 8; i++)
    {
        ui_text(1, CTL_X, CTL_Y - 14 + i * 13, ctl_lines[i][0], K[K_READH]);
        ui_text(0, CTL_X + 108, CTL_Y - 12 + i * 13, ctl_lines[i][1], K[K_TEXT]);
    }
    ui_show();
    IN_Ack();
}

/* -------------------------------------------------------- load / save */

#define LSM_X   85
#define LSM_Y   55
#define LSM_W   175
#define LSM_H   (SAVE_SLOTS * 13 + 10)

static mitem_t LSMenu[SAVE_SLOTS];
static minfo_t LSItems = { LSM_X, LSM_Y, SAVE_SLOTS, 0, 24, 150 };
static char lsnames[SAVE_SLOTS][SAVE_NAMELEN];

static void draw_ls(boolean saving)
{
    s16 i;
    ui_clear();
    drawpic(112, 184, C_MOUSELBACKPIC);
    ui_stripes(10);
    drawpic(saving ? 60 : 60, 0, saving ? C_SAVEGAMEPIC : C_LOADGAMEPIC);
    ui_window(LSM_X - 10, LSM_Y - 5, LSM_W, LSM_H);
    for (i = 0; i < SAVE_SLOTS; i++)
    {
        if (Save_Used(i))
        {
            Save_Name(i, lsnames[i]);
            LSMenu[i].s = lsnames[i];
            LSMenu[i].active = 1;
        }
        else
        {
            LSMenu[i].s = "- empty -";
            LSMenu[i].active = saving ? 1 : 0;
        }
    }
    LSItems.curpos = 0;
}

static boolean cp_load(void)
{
    s16 which;
    ui_open(PG_MENU, ui_kmenu);
    draw_ls(FALSE);
    menu_prepare(&LSItems, LSMenu, NULL);
    ui_show();
    for (;;)
    {
        which = handle_menu(&LSItems, LSMenu, NULL);
        if (which < 0)
            return FALSE;
        if (!Save_Used(which))
        {
            SD_PlaySound(NOWAYSND);
            continue;
        }
        if (Save_Read(which))
        {
            loadedgame = TRUE;
            return TRUE;
        }
        SD_PlaySound(NOWAYSND);
        ui_message("Saved game is damaged!");
        IN_Ack();
        draw_ls(FALSE);
        menu_prepare(&LSItems, LSMenu, NULL);
        vid_update();
    }
}

static void cp_save(void)
{
    s16 which;
    char name[SAVE_NAMELEN];
    ui_open(PG_MENU, ui_kmenu);
    draw_ls(TRUE);
    menu_prepare(&LSItems, LSMenu, NULL);
    ui_show();
    which = handle_menu(&LSItems, LSMenu, NULL);
    if (which < 0)
        return;
    if (Save_Used(which))
    {
        if (!ui_confirm("Overwrite saved game?\n(A = yes, B = no)"))
            return;
    }
    /* "Floor n  score" */
    {
        char *p = name;
        const char *f = "Floor ";
        while (*f) *p++ = *f++;
        ntoa(p, gamestate.mapon + 1);
        while (*p) p++;
        *p++ = ' ';
        __asm__ volatile("" ::: "memory");
        *p++ = ' ';
        ntoa(p, gamestate.score);
    }
    name[SAVE_NAMELEN - 1] = 0;
    if (!Save_Write(which, name))
    {
        SD_PlaySound(NOWAYSND);
        ui_message("Save failed!");
        IN_Ack();
    }
}

/* ----------------------------------------------------------- read this */

#define BACKCOLOR_UNUSED 0
#define TOPMARGIN       16
#define LEFTMARGIN      16
#define RIGHTMARGIN     16
#define FONTHEIGHT      10
#define TEXTROWS        ((200 - TOPMARGIN - 32) / FONTHEIGHT)
#define PICMARGIN       8
#define SPACEWIDTH      7
#define SCREENMID       160

static s16 pagenum, numpages;
static s16 leftmargin[TEXTROWS], rightmargin[TEXTROWS];
static const char *text;
static s16 rowon, px, py;
static boolean layoutdone;
static u8 fontcolor;
static u8 help_back, help_pagecol, help_black;

static u8 help_color(u8 code)
{
    s16 i;
    for (i = 0; i < HELP_NCOLORS; i++)
        if (help_cmap[i][0] == code)
            return help_cmap[i][1];
    return help_black;
}

static void rip_to_eol(void)
{
    while (*text++ != '\n')
        ;
}

static s16 parse_number(void)
{
    s16 n = 0;
    while (*text < '0' || *text > '9')
        text++;
    while (*text >= '0' && *text <= '9')
        n = n * 10 + (*text++ - '0');
    return n;
}

static s16 hexval(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

static void new_line(void)
{
    if (++rowon == TEXTROWS)
    {
        layoutdone = TRUE;
        for (;;)
        {
            if (*text == '^' && (text[1] == 'E' || text[1] == 'e' || text[1] == 'P' || text[1] == 'p'))
                return;
            text++;
        }
    }
    px = leftmargin[rowon];
    py += FONTHEIGHT;
}

static void handle_command(void)
{
    s16 i, margin, top, bottom, picx, picy, picnum, pw, ph, picmid;
    u16 w, h;
    char c = *++text;
    if (c >= 'a' && c <= 'z') c -= 32;
    switch (c)
    {
    case 'B':
        picy = parse_number(); picx = parse_number();
        pw = parse_number(); ph = parse_number();
        ui_bar(picx, picy, pw, ph, help_back);
        rip_to_eol();
        break;
    case ';':
        rip_to_eol();
        break;
    case 'P':
    case 'E':
        layoutdone = TRUE;
        text--;
        break;
    case 'C':
        i = hexval(*++text) * 16;
        i += hexval(*++text);
        fontcolor = help_color((u8)i);
        text++;
        break;
    case '>':
        px = 160;
        text++;
        break;
    case 'L':
        py = parse_number();
        rowon = (py - TOPMARGIN) / FONTHEIGHT;
        py = TOPMARGIN + rowon * FONTHEIGHT;
        px = parse_number();
        while (*text++ != '\n')
            ;
        break;
    case 'T':   /* timed picture: just draw it */
    case 'G':
        picy = parse_number(); picx = parse_number(); picnum = parse_number();
        if (c == 'T') parse_number();
        rip_to_eol();
        drawpic(picx & ~7, picy, picnum);
        pic_size(picnum, &w, &h);
        pw = w; ph = h;
        picmid = picx + pw / 2;
        if (picmid > SCREENMID)
            margin = picx - PICMARGIN;
        else
            margin = picx + pw + PICMARGIN;
        top = (picy - TOPMARGIN) / FONTHEIGHT;
        if (top < 0) top = 0;
        bottom = (picy + ph - TOPMARGIN) / FONTHEIGHT;
        if (bottom >= TEXTROWS) bottom = TEXTROWS - 1;
        for (i = top; i <= bottom; i++)
        {
            if (picmid > SCREENMID)
                rightmargin[i] = margin;
            else
                leftmargin[i] = margin;
        }
        if (px < leftmargin[rowon])
            px = leftmargin[rowon];
        break;
    }
}

static void handle_word(void)
{
    char word[80];
    s16 n = 0, wwidth;
    word[n++] = *text++;
    while (*text > 32 && n < 79)
        word[n++] = *text++;
    word[n] = 0;
    wwidth = txt_width(0, word);
    while (px + wwidth > rightmargin[rowon])
    {
        new_line();
        if (layoutdone)
            return;
    }
    txt_draw(SF, 0, px, py, word, fontcolor);
    px += wwidth;
    while (*text == ' ')
    {
        px += SPACEWIDTH;
        text++;
    }
}

static void page_layout(void)
{
    s16 i;
    char str[24], num[8];

    fontcolor = help_black;
    ui_bar(0, 0, 320, 200, help_back);
    drawpic(0, 0, H_TOPWINDOWPIC);
    drawpic(0, 8, H_LEFTWINDOWPIC);
    drawpic(312, 8, H_RIGHTWINDOWPIC);
    drawpic(8, 176, H_BOTTOMINFOPIC);
    for (i = 0; i < TEXTROWS; i++)
    {
        leftmargin[i] = LEFTMARGIN;
        rightmargin[i] = 320 - RIGHTMARGIN;
    }
    px = LEFTMARGIN;
    py = TOPMARGIN;
    rowon = 0;
    layoutdone = FALSE;

    while (*text <= 32)
        text++;
    text++;                 /* '^' */
    text++;                 /* 'P' */
    while (*text++ != '\n')
        ;
    do
    {
        char ch = *text;
        if (ch == '^')
            handle_command();
        else if (ch == 9)
        {
            px = (px + 8) & 0xF8;
            text++;
        }
        else if (ch <= 32)
        {
            text++;
            if (ch == '\n')
                new_line();
        }
        else
            handle_word();
    } while (!layoutdone);
    pagenum++;

    strcpy(str, "pg ");
    ntoa(num, pagenum);
    strcat(str, num);
    strcat(str, " of ");
    ntoa(num, numpages);
    strcat(str, num);
    ui_text(0, 213, 183, str, help_pagecol);
}

static void back_page(void)
{
    pagenum--;
    for (;;)
    {
        text--;
        if (*text == '^' && (text[1] == 'P' || text[1] == 'p'))
            return;
    }
}

static void show_article(const char *article)
{
    boolean newpage = TRUE, first = TRUE;
    const char *p;

    help_black = help_color(0x00);
    help_back = help_color(0x11);
    help_pagecol = help_color(0x4F);
    text = article;
    pagenum = 0;
    numpages = 0;
    for (p = article; *p; p++)
        if (p[0] == '^' && (p[1] == 'P' || p[1] == 'p'))
            numpages++;
    ui_open(PG_HELP, ui_kmenu);
    for (;;)
    {
        if (newpage)
        {
            newpage = FALSE;
            page_layout();
            vid_update();
            if (first)
            {
                vid_fade_to(pic_group_pal[PG_HELP], NULL, NULL, 10);
                first = FALSE;
            }
        }
        vid_frame();
        IN_Update();
        if (in_pressed & (BUTTON_UP | BUTTON_LEFT))
        {
            if (pagenum > 1)
            {
                back_page();
                back_page();
                newpage = TRUE;
            }
        }
        else if (in_pressed & (BUTTON_DOWN | BUTTON_RIGHT | BUTTON_A | BUTTON_C))
        {
            if (pagenum < numpages)
                newpage = TRUE;
            else if (in_pressed & (BUTTON_A | BUTTON_C))
                break;
        }
        if (in_pressed & (BUTTON_B | BUTTON_START))
            break;
    }
    ui_hide();
}

void HelpScreens(void)
{
    SD_StartMusic(CORNER_MUS);
    show_article(help_text);
}

void EndText(void)
{
    show_article(end_text);
}

/* --------------------------------------------------------- control panel */

static void start_menu_music(void)
{
    if (MusicOn)
        SD_StartMusic(WONDERIN_MUS);
}

void US_ControlPanel(void)
{
    s16 which;
    boolean redraw = TRUE;

    start_menu_music();
    MainItems.curpos = 0;
    ui_open(PG_MENU, ui_kmenu);
    for (;;)
    {
        if (redraw)
        {
            draw_main_menu();
            menu_prepare(&MainItems, MainMenu, NULL);
            ui_show();
            redraw = FALSE;
        }
        which = handle_menu(&MainItems, MainMenu, NULL);
        switch (which)
        {
        case M_NEW:
            if (cp_new_game())
                goto done;
            redraw = TRUE;
            break;
        case M_SOUND:
            cp_sound();
            redraw = TRUE;
            break;
        case M_CONTROL:
            cp_control();
            redraw = TRUE;
            break;
        case M_LOAD:
            if (cp_load())
                goto done;
            redraw = TRUE;
            break;
        case M_SAVE:
            cp_save();
            redraw = TRUE;
            break;
        case M_READ:
            HelpScreens();
            start_menu_music();
            redraw = TRUE;
            break;
        case M_SCORES:
            ViewScores();
            redraw = TRUE;
            break;
        case M_BACK:
        case -1:
            goto done;
        }
        ui_open(PG_MENU, ui_kmenu);
    }
done:
    SD_MusicOff();
    ui_hide();
}
