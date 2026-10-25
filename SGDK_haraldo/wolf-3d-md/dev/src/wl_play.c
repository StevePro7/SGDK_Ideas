/* wl_play.c - the play loop, actor list and controls (port of WL_PLAY.C) */
#include "wl_def.h"
#include "snd.h"
#include "vid.h"
#include "input.h"
#include "hud.h"
#include "menu.h"
#include <string.h>

boolean madenoise;
exit_t playstate;
objtype objlist[MAXACTORS];
objtype *newobj, *obj, *player, *lastobj, *objfreelist, *killerobj;
boolean singlestep, godmode, noclip;
s16 extravbls;

u8 tilemap[MAPSIZE][MAPSIZE];
u8 actorat[MAPSIZE][MAPSIZE];

s16 tics;
s32 lasttimecount;
boolean fizzlein;
boolean startgame, loadedgame;

s16 controlx, controly;
boolean buttonstate[NUMBUTTONS];
boolean buttonheld[NUMBUTTONS];
s16 shootdelta = VIEWW / 10;

/* songs of the first episode, indexed by level */
const s16 songs[10] =
{
    GETTHEM_MUS, SEARCHN_MUS, POW_MUS, SUSPENSE_MUS,
    GETTHEM_MUS, SEARCHN_MUS, POW_MUS, SUSPENSE_MUS,
    WARMARCH_MUS, CORNER_MUS
};

#define BASEMOVE    35
#define RUNMOVE     70
#define MAXTICS     10

/* ---------------------------------------------------------- controls */

static u16 weaponcycle_pending;

static void PollPadButtons(void)
{
    u16 j = in_held;
    if (j & BUTTON_B) buttonstate[bt_attack] = TRUE;
    if (j & BUTTON_A) buttonstate[bt_run] = TRUE;
    if (j & BUTTON_C)
    {
        buttonstate[bt_strafe] = (j & (BUTTON_LEFT | BUTTON_RIGHT)) != 0;
        /* the use key also strafes: only "use" when not sliding sideways */
        buttonstate[bt_use] = TRUE;
    }
    if (j & BUTTON_X) buttonstate[bt_readyknife] = TRUE;
    if (j & BUTTON_Y) buttonstate[bt_readypistol] = TRUE;
    if (j & BUTTON_Z) buttonstate[bt_readymachinegun] = TRUE;
}

/* A + C together: step through the weapons you own */
static void CycleWeapon(void)
{
    s16 w = gamestate.chosenweapon, n;
    if (!gamestate.ammo)
        return;
    for (n = 0; n < 4; n++)
    {
        w++;
        if (w > gamestate.bestweapon) w = wp_knife;
        if (w >= wp_knife)
        {
            gamestate.weapon = gamestate.chosenweapon = (weapontype)w;
            DrawWeapon();
            return;
        }
    }
}

void CalcTics(void)
{
    s32 newtime;

    if (lasttimecount > (s32)TimeCount)
        TimeCount = lasttimecount;
    do
    {
        newtime = TimeCount;
        tics = newtime - lasttimecount;
    } while (!tics);
    lasttimecount = newtime;
    if (tics > MAXTICS)
    {
        TimeCount -= (tics - MAXTICS);
        tics = MAXTICS;
    }
}

void PollControls(void)
{
    s16 max, min;

    CalcTics();

    controlx = 0;
    controly = 0;
    memcpy(buttonheld, buttonstate, sizeof(buttonstate));
    memset(buttonstate, 0, sizeof(buttonstate));

    IN_Update();
    PollPadButtons();

    /* A+C: change weapon instead of using */
    if ((in_held & BUTTON_A) && (in_pressed & BUTTON_C))
    {
        CycleWeapon();
        buttonstate[bt_use] = FALSE;
        buttonheld[bt_use] = TRUE;
    }
    else if ((in_pressed & BUTTON_C) && (in_held & BUTTON_A))
        buttonstate[bt_use] = FALSE;

    {
        s16 m = buttonstate[bt_run] ? RUNMOVE : BASEMOVE;
        if (in_held & BUTTON_UP) controly -= m * tics;
        if (in_held & BUTTON_DOWN) controly += m * tics;
        if (in_held & BUTTON_LEFT) controlx -= m * tics;
        if (in_held & BUTTON_RIGHT) controlx += m * tics;
    }

    max = 100 * tics;
    min = -max;
    if (controlx > max) controlx = max;
    else if (controlx < min) controlx = min;
    if (controly > max) controly = max;
    else if (controly < min) controly = min;
}

/* ------------------------------------------------------------ actors */

static s16 objcount;

void InitActorList(void)
{
    s16 i;

    for (i = 0; i < MAXACTORS; i++)
    {
        objlist[i].prev = &objlist[i + 1];
        objlist[i].next = NULL;
    }
    objlist[MAXACTORS - 1].prev = NULL;

    objfreelist = &objlist[0];
    lastobj = NULL;
    objcount = 0;

    GetNewActor();
    player = newobj;
}

void GetNewActor(void)
{
    if (!objfreelist)
        Quit("GetNewActor: No free spots in objlist!");

    newobj = objfreelist;
    objfreelist = newobj->prev;
    memset(newobj, 0, sizeof(*newobj));

    if (lastobj)
        lastobj->next = newobj;
    newobj->prev = lastobj;
    newobj->active = FALSE;
    lastobj = newobj;
    objcount++;
}

void RemoveObj(objtype *gone)
{
    if (gone == player)
        Quit("RemoveObj: Tried to remove the player!");

    gone->state = NULL;

    if (gone == lastobj)
        lastobj = (objtype *)gone->prev;
    else
        gone->next->prev = gone->prev;

    gone->prev->next = gone->next;

    gone->prev = objfreelist;
    objfreelist = gone;
    objcount--;
}

/* ------------------------------------------------------- palette shifts */

#define NUMREDSHIFTS    6
#define REDSTEPS        8
#define NUMWHITESHIFTS  3
#define WHITESTEPS      20
#define WHITETICS       6

extern u16 game_pal0[16];
extern u16 game_pal1[16];
static s16 damagecount, bonuscount;
static boolean palshifted;

void ClearPaletteShifts(void)
{
    bonuscount = damagecount = 0;
}

void StartBonusFlash(void)
{
    bonuscount = NUMWHITESHIFTS * WHITETICS;
}

void StartDamageFlash(s16 damage)
{
    damagecount += damage;
}

static void ApplyShift(s16 r, s16 g, s16 b, u16 level, u16 levels)
{
    u16 p0[16], p1[16];
    vid_tint(game_pal0, p0, r, g, b, level, levels);
    vid_tint(game_pal1, p1, r, g, b, level, levels);
    vid_set_pal(0, p0);
    vid_set_pal(1, p1);
}

void UpdatePaletteShifts(void)
{
    s16 red, white;

    if (bonuscount)
    {
        white = bonuscount / WHITETICS + 1;
        if (white > NUMWHITESHIFTS) white = NUMWHITESHIFTS;
        bonuscount -= tics;
        if (bonuscount < 0) bonuscount = 0;
    }
    else
        white = 0;

    if (damagecount)
    {
        red = damagecount / 10 + 1;
        if (red > NUMREDSHIFTS) red = NUMREDSHIFTS;
        damagecount -= tics;
        if (damagecount < 0) damagecount = 0;
    }
    else
        red = 0;

    if (red)
    {
        ApplyShift(7, 0, 0, red, REDSTEPS);
        palshifted = TRUE;
    }
    else if (white)
    {
        ApplyShift(7, 7, 0, white, WHITESTEPS);
        palshifted = TRUE;
    }
    else if (palshifted)
    {
        vid_set_pal(0, game_pal0);
        vid_set_pal(1, game_pal1);
        palshifted = FALSE;
    }
}

void FinishPaletteShifts(void)
{
    if (palshifted)
    {
        palshifted = FALSE;
        vid_set_pal(0, game_pal0);
        vid_set_pal(1, game_pal1);
    }
}

/* ------------------------------------------------------------- actors */

static void DoActor(objtype *ob)
{
    void (*think)(objtype *);

    if (!ob->active && !areabyplayer[ob->areanumber])
        return;

    if (!(ob->flags & (FL_NONMARK | FL_NEVERMARK)))
        actorat[ob->tilex][ob->tiley] = 0;

    if (!ob->ticcount)
    {
        think = ob->state->think;
        if (think)
        {
            think(ob);
            if (!ob->state)
            {
                RemoveObj(ob);
                return;
            }
        }

        if (ob->flags & FL_NEVERMARK)
            return;

        if ((ob->flags & FL_NONMARK) && actorat[ob->tilex][ob->tiley])
            return;

        actorat[ob->tilex][ob->tiley] = act_enc(ob);
        return;
    }

    ob->ticcount -= tics;
    while (ob->ticcount <= 0)
    {
        think = ob->state->action;
        if (think)
        {
            think(ob);
            if (!ob->state)
            {
                RemoveObj(ob);
                return;
            }
        }

        ob->state = ob->state->next;

        if (!ob->state)
        {
            RemoveObj(ob);
            return;
        }

        if (!ob->state->tictime)
        {
            ob->ticcount = 0;
            goto dothink;
        }

        ob->ticcount += ob->state->tictime;
    }

dothink:
    think = ob->state->think;
    if (think)
    {
        think(ob);
        if (!ob->state)
        {
            RemoveObj(ob);
            return;
        }
    }

    if (ob->flags & FL_NEVERMARK)
        return;

    if ((ob->flags & FL_NONMARK) && actorat[ob->tilex][ob->tiley])
        return;

    actorat[ob->tilex][ob->tiley] = act_enc(ob);
}

/* --------------------------------------------------------------- music */

void StartMusic(void)
{
    SD_StartLevelMusic(songs[gamestate.mapon % 10]);
}

void StopMusic(void)
{
    SD_MusicOff();
}

/* ---------------------------------------------------------- play loop */

static void CheckKeys(void)
{
    if (in_pressed & BUTTON_START)
    {
        StopMusic();
        FinishPaletteShifts();
        US_ControlPanel();
        if (!startgame && !loadedgame)
            StartMusic();
        if (loadedgame)
            playstate = ex_abort;
        lasttimecount = TimeCount;
        IN_ClearKeys();
    }
}

void PlayLoop(void)
{
    playstate = ex_stillplaying;
    TimeCount = lasttimecount = 0;
    running = FALSE;
    anglefrac = 0;
    facecount = 0;
    memset(buttonstate, 0, sizeof(buttonstate));
    ClearPaletteShifts();
    IN_ClearKeys();

    do
    {
        PollControls();

        madenoise = FALSE;
        MoveDoors();
        MovePWalls();

        for (obj = player; obj; obj = obj->next)
            DoActor(obj);

        UpdatePaletteShifts();

        ThreeDRefresh();

        gamestate.TimeCount += tics;
#if defined(WOLF_TEST) && WOLF_TEST == 1
        if (gamestate.TimeCount > 400) { gamestate.killcount = gamestate.killtotal; gamestate.treasurecount = gamestate.treasuretotal / 2; playstate = ex_completed; }
#elif defined(WOLF_TEST) && WOLF_TEST == 2
        if (gamestate.TimeCount > 100) playstate = ex_victorious;
#endif

        UpdateSoundLoc();

        CheckKeys();
    } while (!playstate && !startgame);

    if (playstate != ex_died)
        FinishPaletteShifts();
}
