/* wl_game.c - level setup, play screen and the game loop (port of WL_GAME.C) */
#include "wl_def.h"
#include "snd.h"
#include "vid.h"
#include "input.h"
#include "hud.h"
#include "pic.h"
#include "menu.h"
#include "inter.h"
#include <string.h>

gametype gamestate;
u8 mapplane0[MAPSIZE * MAPSIZE];
const u16 *mapplane1;

static const s16 ElevatorBackTo[6] = { 1, 1, 7, 3, 5, 3 };

extern const u8 righttable[15 * 30], lefttable[15 * 30];
#define ATABLEMAX 15

static s32 globalsoundx, globalsoundy;
static s16 leftchannel, rightchannel;

/* ------------------------------------------------------- positioned sound */

static void SetSoundLoc(s32 gx, s32 gy)
{
    s32 xt, yt;
    s16 x, y;

    gx -= viewx;
    gy -= viewy;

    xt = FixedByFrac(gx, viewcos);
    yt = FixedByFrac(gy, viewsin);
    x = (xt - yt) >> TILESHIFT;

    xt = FixedByFrac(gx, viewsin);
    yt = FixedByFrac(gy, viewcos);
    y = (yt + xt) >> TILESHIFT;

    if (y >= ATABLEMAX) y = ATABLEMAX - 1;
    else if (y <= -ATABLEMAX) y = -ATABLEMAX;
    if (x < 0) x = -x;
    if (x >= ATABLEMAX) x = ATABLEMAX - 1;
    leftchannel = lefttable[x * 30 + y + ATABLEMAX];
    rightchannel = righttable[x * 30 + y + ATABLEMAX];
}

void PlaySoundLocGlobal(u16 s, s32 gx, s32 gy)
{
    SetSoundLoc(gx, gy);
    SD_PositionSound(leftchannel, rightchannel);
    if (SD_PlaySound(s))
    {
        globalsoundx = gx;
        globalsoundy = gy;
    }
}

void UpdateSoundLoc(void)
{
    if (SD_SoundPositioned())
    {
        SetSoundLoc(globalsoundx, globalsoundy);
        SD_SetPosition(leftchannel, rightchannel);
    }
}

/* -------------------------------------------------------- level scanning */

typedef struct { u16 base; u8 en; u8 patrol; u8 step; } enemygroup_t;
static const enemygroup_t groups[] =
{
    { 108, en_guard, 0, 36 }, { 112, en_guard, 1, 36 },
    { 116, en_officer, 0, 36 }, { 120, en_officer, 1, 36 },
    { 126, en_ss, 0, 36 }, { 130, en_ss, 1, 36 },
    { 134, en_dog, 0, 36 }, { 138, en_dog, 1, 36 },
    { 216, en_mutant, 0, 18 }, { 220, en_mutant, 1, 18 }
};

static boolean ScanEnemy(u16 tile, s16 x, s16 y)
{
    u8 i;
    for (i = 0; i < sizeof(groups) / sizeof(groups[0]); i++)
    {
        const enemygroup_t *g = &groups[i];
        s16 off = tile - g->base;
        s16 level = 0;
        if (off >= 2 * g->step) { off -= 2 * g->step; level = gd_hard; }
        else if (off >= g->step) { off -= g->step; level = gd_medium; }
        if (off >= 0 && off < 4)
        {
            if (gamestate.difficulty < level)
                return TRUE;
            if (g->patrol)
                SpawnPatrol((enemy_t)g->en, x, y, off);
            else
                SpawnStand((enemy_t)g->en, x, y, off);
            return TRUE;
        }
    }
    return FALSE;
}

void ScanInfoPlane(void)
{
    s16 x, y;
    u16 tile;
    const u16 *start = mapplane1;

    for (y = 0; y < MAPSIZE; y++)
        for (x = 0; x < MAPSIZE; x++)
        {
            tile = *start++;
            if (!tile)
                continue;

            if (tile >= 19 && tile <= 22)
                SpawnPlayer(x, y, NORTH + tile - 19);
            else if (tile >= 23 && tile <= 74)
                SpawnStatic(x, y, tile - 23);
            else if (tile == 98)
            {
                if (!loadedgame)
                    gamestate.secrettotal++;
            }
            else if (tile == 124)
                SpawnDeadGuard(x, y);
            else if (tile == 214) SpawnBoss(x, y);
            else if (tile == 197) SpawnGretel(x, y);
            else if (tile == 215) SpawnGift(x, y);
            else if (tile == 179) SpawnFat(x, y);
            else if (tile == 196) SpawnSchabbs(x, y);
            else if (tile == 160) SpawnFakeHitler(x, y);
            else if (tile == 178) SpawnHitler(x, y);
            else if (tile >= 224 && tile <= 227)
                SpawnGhosts(en_blinky + tile - 224, x, y);
            else
                ScanEnemy(tile, x, y);
        }
}

void SetupGameLevel(void)
{
    s16 x, y, i;
    u16 tile, spot;
    const mapinfo_t *mi = &mapinfo[gamestate.mapon];

    if (!loadedgame)
    {
        gamestate.TimeCount =
        gamestate.secrettotal =
        gamestate.killtotal =
        gamestate.treasuretotal =
        gamestate.secretcount =
        gamestate.killcount =
        gamestate.treasurecount = 0;
    }

    US_InitRndT(TRUE);

    memcpy(mapplane0, mi->p0, MAPSIZE * MAPSIZE);
    mapplane1 = mi->p1;
    R_SetLevelColors(mi->ceilcolor);

    memset(tilemap, 0, sizeof(tilemap));
    memset(actorat, 0, sizeof(actorat));
    for (y = 0; y < MAPSIZE; y++)
        for (x = 0; x < MAPSIZE; x++)
        {
            tile = MAPSPOT0(x, y);
            if (tile < AREATILE)
            {
                tilemap[x][y] = tile;
                actorat[x][y] = (tile < 64) ? tile : 1;
            }
            else
            {
                tilemap[x][y] = 0;
                actorat[x][y] = 0;
            }
        }

    InitActorList();
    InitDoorList();
    InitStaticList();

    for (y = 0; y < MAPSIZE; y++)
        for (x = 0; x < MAPSIZE; x++)
        {
            tile = MAPSPOT0(x, y);
            if (tile >= 90 && tile <= 101)
            {
                if (!(tile & 1))
                    SpawnDoor(x, y, 1, (tile - 90) / 2);
                else
                    SpawnDoor(x, y, 0, (tile - 91) / 2);
            }
        }

    ScanInfoPlane();

    /* take out the ambush markers */
    for (y = 0; y < MAPSIZE; y++)
        for (x = 0; x < MAPSIZE; x++)
        {
            u8 *map = &mapplane0[(y << 6) + x];
            tile = *map;
            if (tile == AMBUSHTILE)
            {
                tilemap[x][y] = 0;
                if (actorat[x][y] == 1)
                    actorat[x][y] = 0;
                spot = 0;
                if (x < MAPSIZE - 1 && *(map + 1) >= AREATILE)
                    tile = *(map + 1);
                if (y > 0 && x > 0 && *(map - 1 - MAPSIZE) >= AREATILE)
                    tile = *(map - 1 - MAPSIZE);
                if (y < MAPSIZE - 1 && x > 0 && *(map - 1 + MAPSIZE) >= AREATILE)
                    tile = *(map - 1 + MAPSIZE);
                if (x > 1 && *(map - 2) >= AREATILE)
                    tile = *(map - 2);
                *map = tile;
            }
        }
    (void)i;
}

/* ------------------------------------------------------------ play screen */

u16 border_pal[16];

void DrawStatusBar(void)
{
    pic_draw(&statsurf, 0, 0, STATUSBARPIC);
    DrawFace();
    DrawHealth();
    DrawLives();
    DrawLevel();
    DrawAmmo();
    DrawKeys();
    DrawWeapon();
    DrawScore();
    vid_flush(&statsurf);
}

void DrawPlayScreen(void)
{
    vid_fade_out(8);
    vid_game_mode();
    memset(border_pal, 0, sizeof(border_pal));
    border_pal[1] = border_color;
    DrawStatusBar();
    vid_wait_idle();
}

static void FadeInLevel(void)
{
    vid_fade_to(game_pal0, game_pal1, border_pal, 20);
}

/* ------------------------------------------------------------- death cam */

void DeathCamIntro(void)
{
    FinishPaletteShifts();
    vid_fade_out(10);
    ThreeDRefresh();
    ThreeDRefresh();
    vid_fade_to(game_pal0, game_pal1, border_pal, 10);
}

/* ------------------------------------------------------------------ died */

#define DEATHROTATE 2

void Died(void)
{
    s32 dx, dy;
    s16 iangle, curangle, clockwise, counter, change;

    gamestate.weapon = (weapontype)-1;
    SD_PlaySound(PLAYERDEATHSND);

    dx = killerobj->x - player->x;
    dy = player->y - killerobj->y;
    iangle = AimAngle(dy, dx);

    if (player->angle > iangle)
    {
        counter = player->angle - iangle;
        clockwise = ANGLES - player->angle + iangle;
    }
    else
    {
        clockwise = iangle - player->angle;
        counter = player->angle + ANGLES - iangle;
    }

    curangle = player->angle;
    if (clockwise < counter)
    {
        if (curangle > iangle) curangle -= ANGLES;
        do
        {
            change = tics * DEATHROTATE;
            if (curangle + change > iangle) change = iangle - curangle;
            curangle += change;
            player->angle += change;
            if (player->angle >= ANGLES) player->angle -= ANGLES;
            ThreeDRefresh();
            CalcTics();
        } while (curangle != iangle);
    }
    else
    {
        if (curangle < iangle) curangle += ANGLES;
        do
        {
            change = -tics * DEATHROTATE;
            if (curangle + change < iangle) change = iangle - curangle;
            curangle += change;
            player->angle += change;
            if (player->angle < 0) player->angle += ANGLES;
            ThreeDRefresh();
            CalcTics();
        } while (curangle != iangle);
    }

    FinishPaletteShifts();

    /* red out the view, then wait for a key */
    IN_ClearKeys();
    Inter_FadeToColor(0x00E);       /* dark red */
    IN_UserInput(100);
    SD_WaitSoundDone();

    gamestate.lives--;

    if (gamestate.lives > -1)
    {
        gamestate.health = 100;
        gamestate.weapon = gamestate.bestweapon = gamestate.chosenweapon = wp_pistol;
        gamestate.ammo = STARTAMMO;
        gamestate.keys = 0;
        gamestate.attackframe = gamestate.attackcount = gamestate.weaponframe = 0;

        DrawKeys();
        DrawWeapon();
        DrawAmmo();
        DrawHealth();
        DrawFace();
        DrawLives();
    }
}

/* ------------------------------------------------------------- game loop */

void GameLoop(void)
{
    boolean died;

    ingame = TRUE;

restartgame:
    StopMusic();
    DrawPlayScreen();
    died = FALSE;
    do
    {
        if (!loadedgame)
            gamestate.score = gamestate.oldscore;
        DrawScore();

        startgame = FALSE;
        if (loadedgame)
            loadedgame = FALSE;
        else
            SetupGameLevel();

        StartMusic();

        if (!died)
            Inter_GetPsyched();
        else
            died = FALSE;

        fizzlein = TRUE;
        DrawLevel();

        /* prime both view buffers while the screen is dark */
        vid_black();
        ThreeDRefresh();
        ThreeDRefresh();
        vid_wait_idle();
        FadeInLevel();

        PlayLoop();

        StopMusic();

        if (startgame || loadedgame)
            goto restartgame;

        switch (playstate)
        {
        case ex_completed:
        case ex_secretlevel:
            gamestate.keys = 0;
            DrawKeys();
            vid_fade_out(10);
            LevelCompleted();
            gamestate.oldscore = gamestate.score;
            if (gamestate.mapon == 9)
                gamestate.mapon = ElevatorBackTo[gamestate.episode];
            else if (playstate == ex_secretlevel)
                gamestate.mapon = 9;
            else
                gamestate.mapon++;
            DrawPlayScreen();
            break;

        case ex_died:
            Died();
            died = TRUE;
            if (gamestate.lives > -1)
                break;
            vid_fade_out(10);
            ingame = FALSE;
            CheckHighScore(gamestate.score, gamestate.mapon + 1);
            return;

        case ex_victorious:
            vid_fade_out(10);
            Victory();
            ingame = FALSE;
            CheckHighScore(gamestate.score, gamestate.mapon + 1);
            return;

        default:
            break;
        }
    } while (1);
}
