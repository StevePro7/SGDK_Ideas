/* inter.c - intermission, victory, high scores, title screens (port of WL_INTER.C) */
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

extern u16 game_pal0[16];
extern u16 game_pal1[16];

/* ------------------------------------------------------------- Write() */

static void put(s16 x, s16 y, u16 pic)
{
    pic_draw(&fullsurf, x, y, pic);
}

/* the original's big-digit font made of pictures; x in 8 pixel columns, y in 8 pixel rows */
static void Write(s16 x, s16 y, const char *s)
{
    s16 ox, nx, ny;
    char ch;
    ox = nx = x * 8;
    ny = y * 8;
    for (; *s; s++)
    {
        ch = *s;
        if (ch == '\n') { nx = ox; ny += 16; continue; }
        if (ch >= 'a' && ch <= 'z') ch -= 32;
        if (ch == '!') { put(nx, ny, L_EXPOINTPIC); nx += 8; continue; }
        if (ch == '\'') { put(nx, ny, L_APOSTROPHEPIC); nx += 8; continue; }
        if (ch == ':') { put(nx, ny, L_COLONPIC); nx += 8; continue; }
        if (ch == '%') put(nx, ny, L_PERCENTPIC);
        else if (ch >= '0' && ch <= '9') put(nx, ny, L_NUM0PIC + (ch - '0'));
        else if (ch >= 'A' && ch <= 'Z') put(nx, ny, L_APIC + (ch - 'A'));
        nx += 16;
    }
}

static void write_time(s16 x8, s16 y8row, s16 min, s16 sec)
{
    s16 i = x8 * 8 + (x8 == 14 ? 1 : 0);
    put(i, y8row * 8, L_NUM0PIC + min / 10); i += 16;
    put(i, y8row * 8, L_NUM0PIC + min % 10); i += 16;
    Write(i / 8, y8row, ":"); i += 8;
    put(i, y8row * 8, L_NUM0PIC + sec / 10); i += 16;
    put(i, y8row * 8, L_NUM0PIC + sec % 10);
}

static void BJ_Breathe(void)
{
    static s16 which = 0, max = 10;
    if (TimeCount > (u32)max)
    {
        which ^= 1;
        put(0, 16, which ? L_GUY2PIC : L_GUYPIC);
        vid_update();
        TimeCount = 0;
        max = 35;
    }
}

/* ------------------------------------------------------ level ratios */

u8 ratio_kill[8], ratio_secret[8], ratio_treasure[8];
u16 ratio_time[8];

static void inter_open(void)
{
    K = ui_kinter;
    vid_split_mode();
    vid_black();
    DrawStatusBar();
    ui_bar(0, 0, 320, 160, K[K_VIEW]);
}

static void inter_show(void)
{
    vid_update();
    vid_fade_to(pic_group_pal[PG_INTER], game_pal1, NULL, 10);
}

static void wait_snd(void)
{
    while (SD_SoundPlaying())
    {
        vid_frame();
        BJ_Breathe();
    }
}

static void write_right(s16 xr, s16 y, s32 v)
{
    char t[12];
    ui_itoa(t, v);
    Write(xr - (s16)strlen(t) * 2, y, t);
}

static void ratio_count(s16 ratio, s16 y, s32 *bonus, boolean *abort)
{
    s16 i;
    char t[12];
    for (i = 0; i <= ratio; i++)
    {
        ui_itoa(t, i);
        write_right(37, y, i);
        if (!(i % 10))
            SD_PlaySound(ENDBONUS1SND);
        vid_update();
        vid_frame();
        wait_snd();
        if (IN_CheckAck())
        {
            *abort = TRUE;
            return;
        }
    }
    if (ratio == 100)
    {
        vid_wait(30);
        SD_StopSound();
        *bonus += 10000;
        write_right(36, 7, *bonus);
        vid_update();
        SD_PlaySound(PERCENT100SND);
    }
    else if (!ratio)
    {
        vid_wait(30);
        SD_StopSound();
        SD_PlaySound(NOBONUSSND);
    }
    else
        SD_PlaySound(ENDBONUS2SND);
    vid_update();
    wait_snd();
}

void LevelCompleted(void)
{
    s16 i, min, sec, kr = 0, sr = 0, tr = 0, mapon = gamestate.mapon;
    s32 bonus, timeleft = 0, par;
    boolean abort = FALSE;
    char t[16];

    inter_open();
    SD_StartMusic(ENDLEVEL_MUS);
    IN_ClearKeys();
    put(0, 16, L_GUYPIC);

    if (mapon < 8)
    {
        par = mapinfo[mapon].partics;           /* tics */
        Write(14, 2, "floor\ncompleted");
        Write(14, 7, "bonus     0");
        Write(16, 10, "time");
        Write(16, 12, " par");
        Write(9, 14, "kill ratio    %");
        Write(5, 16, "secret ratio    %");
        Write(1, 18, "treasure ratio    %");
        ui_itoa(t, mapon + 1);
        Write(26, 2, t);
        i = (s16)(par / 70);
        t[0] = '0' + (i / 60) / 10; t[1] = '0' + (i / 60) % 10; t[2] = ':';
        t[3] = '0' + (i % 60) / 10; t[4] = '0' + (i % 60) % 10; t[5] = 0;
        Write(26, 12, t);

        sec = (s16)(gamestate.TimeCount / 70);
        if (sec > 99 * 60) sec = 99 * 60;
        if (gamestate.TimeCount < par)
            timeleft = par / 70 - sec;
        min = sec / 60;
        sec %= 60;
        write_time(26, 10, min, sec);
        inter_show();

        if (gamestate.killtotal)
            kr = (gamestate.killcount * 100) / gamestate.killtotal;
        if (gamestate.secrettotal)
            sr = (gamestate.secretcount * 100) / gamestate.secrettotal;
        if (gamestate.treasuretotal)
            tr = (gamestate.treasurecount * 100) / gamestate.treasuretotal;

        bonus = timeleft * 500;
        if (bonus)
        {
            for (i = 0; i <= timeleft; i++)
            {
                write_right(36, 7, (s32)i * 500);
                if (!(i % 50))
                    SD_PlaySound(ENDBONUS1SND);
                vid_update();
                vid_frame();
                wait_snd();
                if (IN_CheckAck())
                {
                    abort = TRUE;
                    break;
                }
            }
            if (!abort)
            {
                vid_update();
                SD_PlaySound(ENDBONUS2SND);
                wait_snd();
            }
        }
        if (!abort) ratio_count(kr, 14, &bonus, &abort);
        if (!abort) ratio_count(sr, 16, &bonus, &abort);
        if (!abort) ratio_count(tr, 18, &bonus, &abort);

        /* final state, also reached by pressing a button */
        write_right(37, 14, kr);
        write_right(37, 16, sr);
        write_right(37, 18, tr);
        bonus = timeleft * 500 + (kr == 100 ? 10000 : 0) + (sr == 100 ? 10000 : 0) + (tr == 100 ? 10000 : 0);
        GivePoints(bonus);
        write_right(36, 7, bonus);
        ratio_kill[mapon] = kr;
        ratio_secret[mapon] = sr;
        ratio_treasure[mapon] = tr;
        ratio_time[mapon] = min * 60 + sec;
    }
    else
    {
        Write(14, 4, "secret floor\n completed!");
        Write(10, 16, "15000 bonus!");
        inter_show();
        GivePoints(15000);
    }
    DrawScore();
    vid_update();
    TimeCount = 0;
    IN_ClearKeys();
    for (;;)
    {
        vid_frame();
        BJ_Breathe();
        if (IN_CheckAck())
            break;
    }
    vid_fade_out(10);
}

/* --------------------------------------------------------------- victory */

void Victory(void)
{
    s16 i, min, kr = 0, sr = 0, tr = 0;
    s32 sec = 0;
    char t[12];

    inter_open();
    SD_StartMusic(URAHERO_MUS);
    Write(18, 2, "you win!");
    Write(14, 6, "total time");
    Write(12, 12, "averages");
    Write(14, 14, "kill    %");
    Write(10, 16, "secret    %");
    Write(6, 18, "treasure    %");
    put(8, 4, L_BJWINSPIC);

    for (i = 0; i < 8; i++)
    {
        sec += ratio_time[i];
        kr += ratio_kill[i];
        sr += ratio_secret[i];
        tr += ratio_treasure[i];
    }
    kr /= 8; sr /= 8; tr /= 8;
    min = (s16)(sec / 60);
    sec %= 60;
    if (min > 99) min = sec = 99;
    write_time(14, 8, min, (s16)sec);
    ui_itoa(t, kr); Write(6 + 24 - (s16)strlen(t) * 2, 14, t);
    ui_itoa(t, sr); Write(6 + 24 - (s16)strlen(t) * 2, 16, t);
    ui_itoa(t, tr); Write(6 + 24 - (s16)strlen(t) * 2, 18, t);
    inter_show();
    IN_Ack();
    vid_fade_out(10);
    EndText();
}

/* ----------------------------------------------------------- high scores */

#define MAXSCORES   7
#define MAXHIGHNAME 16

typedef struct
{
    char name[MAXHIGHNAME + 1];
    u16 completed;
    s32 score;
} HighScore;

HighScore Scores[MAXSCORES];

static const HighScore default_scores[MAXSCORES] =
{
    { "id software-'92", 1, 10000 },
    { "Adrian Carmack", 1, 10000 },
    { "John Carmack", 1, 10000 },
    { "Kevin Cloud", 1, 10000 },
    { "Tom Hall", 1, 10000 },
    { "John Romero", 1, 10000 },
    { "Jay Wilbur", 1, 10000 },
};

void Scores_Defaults(void)
{
    memcpy(Scores, default_scores, sizeof(Scores));
}

/* raw access for the save module */
void *Scores_Ptr(void) { return Scores; }
u16 Scores_Size(void) { return sizeof(Scores); }

static void fixed_digits(char *s)
{
    for (; *s; s++)
        *s = *s + (129 - '0');      /* fixed width digits live at 129.. in the small font */
}

void DrawHighScores(void)
{
    s16 i;
    char buf[16];
    u8 white = K[K_WHITE];
    ui_clear();
    ui_stripes(10);
    ui_pic(48, 0, HIGHSCORESPIC);
    ui_pic(4 * 8, 68, C_NAMEPIC);
    ui_pic(20 * 8, 68, C_LEVELPIC);
    ui_pic(28 * 8, 68, C_SCOREPIC);
    for (i = 0; i < MAXSCORES; i++)
    {
        s16 y = 76 + 16 * i;
        ui_text(0, 4 * 8, y, Scores[i].name, white);
        ui_itoa(buf, Scores[i].completed);
        fixed_digits(buf);
        ui_text(0, 22 * 8 - txt_width(0, buf), y, buf, white);
        ui_itoa(buf, Scores[i].score);
        fixed_digits(buf);
        ui_text(0, 34 * 8 - 8 - txt_width(0, buf), y, buf, white);
    }
}

void ViewScores(void)
{
    if (MusicOn) SD_StartMusic(ROSTER_MUS);
    ui_open(PG_HSCORE, ui_khs);
    DrawHighScores();
    ui_show();
    IN_Ack();
    ui_hide();
}

static const char charset[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'!";
#define NCHARS ((s16)sizeof(charset) - 1)

/* gamepad line editor: Up/Down change the letter, Right/A/C accept it, Left/B delete, Start finishes */
static void line_input(s16 x, s16 y, char *buf, s16 maxlen)
{
    s16 pos = 0, idx = 1, blink = 0, i;
    u16 hold = 0;
    u8 white = K[K_WHITE];
    buf[0] = charset[idx];
    buf[1] = 0;
    IN_ClearKeys();
    ui_text(0, 8, 188, "Up/Down: letter   Right/A: next   Left/B: delete   Start: done", K[K_TEXT]);
    for (;;)
    {
        s16 dir = 0;
        ui_bar(x - 1, y - 1, 140, 12, K[K_BORD]);
        ui_text(0, x, y, buf, white);
        if (blink & 16)
            ui_bar(x + txt_width(0, buf) - txt_width(0, buf + pos), y + 9, txt_width(0, buf + pos), 1, white);
        vid_update();
        vid_frame();
        blink++;
        IN_Update();
        if (in_pressed & (BUTTON_UP | BUTTON_DOWN)) { hold = 0; dir = (in_pressed & BUTTON_UP) ? 1 : -1; }
        else if (in_held & (BUTTON_UP | BUTTON_DOWN))
        {
            hold++;
            if (hold > 16 && (hold & 3) == 0)
                dir = (in_held & BUTTON_UP) ? 1 : -1;
        }
        else hold = 0;
        if (dir)
        {
            idx += dir;
            if (idx < 0) idx = NCHARS - 1;
            if (idx >= NCHARS) idx = 0;
            buf[pos] = charset[idx];
            SD_PlaySound(MOVEGUN2SND);
        }
        if (in_pressed & (BUTTON_RIGHT | BUTTON_A | BUTTON_C))
        {
            if (pos < maxlen - 1)
            {
                pos++;
                buf[pos] = charset[idx];
                buf[pos + 1] = 0;
                SD_PlaySound(MOVEGUN1SND);
            }
        }
        if (in_pressed & (BUTTON_LEFT | BUTTON_B))
        {
            if (pos > 0)
            {
                buf[pos] = 0;
                pos--;
                for (i = 0; charset[i] != buf[pos]; i++)
                    ;
                idx = i;
                SD_PlaySound(ESCPRESSEDSND);
            }
        }
        if (in_pressed & BUTTON_START)
            break;
    }
    /* trim trailing blanks */
    while (pos >= 0 && buf[pos] == ' ')
        buf[pos--] = 0;
    SD_PlaySound(SHOOTSND);
}

void CheckHighScore(s32 score, u16 other)
{
    s16 i, j, n = -1;
    HighScore my;

    memset(&my, 0, sizeof(my));
    my.score = score;
    my.completed = other;
    for (i = 0; i < MAXSCORES; i++)
    {
        if (my.score > Scores[i].score ||
            (my.score == Scores[i].score && my.completed > Scores[i].completed))
        {
            for (j = MAXSCORES - 1; j > i; j--)
                Scores[j] = Scores[j - 1];
            Scores[i] = my;
            n = i;
            break;
        }
    }
    if (MusicOn) SD_StartMusic(ROSTER_MUS);
    ui_open(PG_HSCORE, ui_khs);
    DrawHighScores();
    ui_show();
    if (n != -1)
    {
        ui_bar(4 * 8 - 1, 76 + 16 * n - 1, 140, 12, K[K_BORD]);
        line_input(4 * 8, 76 + 16 * n, Scores[n].name, MAXHIGHNAME);
        Scores_Store();
        DrawHighScores();
        vid_update();
        IN_UserInput(70 * 4);
    }
    else
        IN_UserInput(70 * 7);
    ui_hide();
    SD_MusicOff();
}

/* -------------------------------------------------------- fades, psyched */

void Inter_FadeToColor(u16 color)
{
    u16 p[16];
    s16 i;
    for (i = 0; i < 16; i++) p[i] = color;
    vid_fade_to(p, p, p, 20);
}

static u8 nearest_red(void)
{
    s16 i, best = 1, bs = -1000;
    for (i = 0; i < 16; i++)
    {
        s16 r = (game_pal0[i] >> 1) & 7, g = (game_pal0[i] >> 5) & 7, b = (game_pal0[i] >> 9) & 7;
        s16 sc = r * 2 - g - b;
        if (sc > bs) { bs = sc; best = i; }
    }
    return best;
}

static u8 view_fill_index(void)
{
    s16 i, best = 0;
    s16 bd = 10000;
    s16 br = (border_color >> 1) & 7, bg = (border_color >> 5) & 7, bb = (border_color >> 9) & 7;
    for (i = 0; i < 16; i++)
    {
        s16 r = (game_pal0[i] >> 1) & 7, g = (game_pal0[i] >> 5) & 7, b = (game_pal0[i] >> 9) & 7;
        s16 d = (r - br) * (r - br) + (g - bg) * (g - bg) + (b - bb) * (b - bb);
        if (d < bd) { bd = d; best = i; }
    }
    return best;
}

void Inter_GetPsyched(void)
{
    s16 x = 16, y = 40, i, w = 214;
    u8 red = nearest_red();
    pic_fill(&viewsurf, 0, 0, VIEWW, VIEWH, view_fill_index());
    pic_draw(&viewsurf, x, y, GETPSYCHEDPIC);
    pic_fill(&viewsurf, x + 5, y + 45, w, 2, 0);
    vid_present_view();
    vid_wait_idle();
    vid_fade_to(game_pal0, game_pal1, border_pal, 10);
    for (i = 1; i <= 8; i++)
    {
        pic_fill(&viewsurf, x + 5, y + 45, (w * i) / 8, 2, red);
        vid_present_view();
        vid_wait_idle();
        vid_wait(7);
    }
    IN_UserInput(20);
}

/* ------------------------------------------------------ title sequence */

void PG13(void)
{
    u8 bg = (pic_data[pic_tab[PG13PIC - PIC_FIRST].ofs]) >> 4;
    ui_open(PG_PG13, ui_kmenu);
    ui_bar(0, 0, 320, 200, bg);
    ui_pic(216, 110, PG13PIC);
    ui_show();
    IN_UserInput(70 * 7);
    ui_hide();
}

/* title, credits and high scores in turn; TRUE as soon as a button is pressed */
boolean AttractLoop(void)
{
    if (MusicOn) SD_StartMusic(NAZI_NOR_MUS);
    for (;;)
    {
        ui_open(PG_TITLE, ui_kmenu);
        ui_pic(0, 0, TITLEPIC);
        ui_show();
        if (IN_UserInput(70 * 15)) { ui_hide(); return TRUE; }

        ui_open(PG_CREDITS, ui_kmenu);
        ui_pic(0, 0, CREDITSPIC);
        ui_show();
        if (IN_UserInput(70 * 10)) { ui_hide(); return TRUE; }

        ui_open(PG_HSCORE, ui_khs);
        DrawHighScores();
        ui_show();
        if (IN_UserInput(70 * 10)) { ui_hide(); return TRUE; }
    }
}
