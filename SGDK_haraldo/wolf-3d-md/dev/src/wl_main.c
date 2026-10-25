/* wl_main.c - startup, new game, main loop (port of WL_MAIN.C) */
#include "wl_def.h"
#include "snd.h"
#include "vid.h"
#include "input.h"
#include "hud.h"
#include "pic.h"
#include "menu.h"
#include "inter.h"
#include "save.h"
#include <string.h>

static u16 rndindex;

void US_InitRndT(boolean randomize)
{
    if (randomize)
        rndindex = (TimeCount + vid_frames) & 0xFF;
    else
        rndindex = 0;
}

u16 US_RndT(void)
{
    rndindex = (rndindex + 1) & 0xFF;
    return rndtable[rndindex];
}

void Quit(const char *error)
{
    SYS_disableInts();
    VDP_setEnable(TRUE);
    VDP_clearPlane(BG_A, TRUE);
    PAL_setColor(15, 0xEEE);
    VDP_drawText(error ? error : "QUIT", 1, 12);
    for (;;) ;
}

void NewGame(s16 difficulty, s16 episode)
{
    memset(&gamestate, 0, sizeof(gamestate));
    gamestate.difficulty = difficulty;
    gamestate.weapon = gamestate.bestweapon = gamestate.chosenweapon = wp_pistol;
    gamestate.health = 100;
    gamestate.ammo = STARTAMMO;
    gamestate.lives = 3;
    gamestate.nextextra = EXTRAPOINTS;
    gamestate.episode = episode;
    startgame = FALSE;
    loadedgame = FALSE;
}

int main(bool hardReset)
{
    vid_init();
    IN_Init();
    HUD_Init();
    R_Init();
    SD_Init();
    Scores_Load();

#if defined(WOLF_TEST) && WOLF_TEST == 3
    NewGame(gd_medium, 0);
    gamestate.mapon = 2;
    CheckHighScore(23456, 3);
#elif defined(WOLF_TEST)
    NewGame(gd_medium, 0);
    startgame = TRUE;
    GameLoop();
#endif
    PG13();
    for (;;)
    {
        startgame = loadedgame = FALSE;
        AttractLoop();
        US_ControlPanel();
        if (startgame || loadedgame)
            GameLoop();
    }
    return 0;
}
