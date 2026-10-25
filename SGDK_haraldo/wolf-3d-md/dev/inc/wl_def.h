/* wl_def.h - Wolfenstein 3D (shareware) definitions, ported to the 68000 */
#ifndef WL_DEF_H
#define WL_DEF_H

#include "wl_types.h"
#include "gen.h"
#include "sprnames.h"

#define SIGN(x)         ((x) > 0 ? 1 : -1)
#define ABS(x)          ((x) > 0 ? (x) : -(x))
#ifndef abs
#define abs(x)          ((x) < 0 ? -(x) : (x))
#endif

#define NUMENEMIES      22
#define ICONARROWS      90
#define SoundBlasterPresent TRUE
#define MAXACTORS       120
#define MAXSTATS        400
#define MAXDOORS        64
#define MAXWALLTILES    64
#define MAPSIZE         64

#define PUSHABLETILE    98
#define EXITTILE        99
#define AREATILE        107
#define NUMAREAS        37
#define ELEVATORTILE    21
#define AMBUSHTILE      106
#define ALTELEVATORTILE 107

#define EXTRAPOINTS     40000
#define PLAYERSPEED     3000
#define RUNSPEED        6000
#define PLAYERSIZE      MINDIST
#define MINACTORDIST    0x10000l

#define GLOBAL1         (1l << 16)
#define TILEGLOBAL      GLOBAL1
#define PIXGLOBAL       (GLOBAL1 / 64)
#define TILESHIFT       16
#define ANGLES          360
#define ANGLEQUAD       (ANGLES / 4)
#define FINEANGLES      3600
#define ANG90           (FINEANGLES / 4)
#define ANG180          (ANG90 * 2)
#define ANG270          (ANG90 * 3)
#define ANG360          (ANG90 * 4)
#define VANG90          (ANGLES / 4)
#define VANG180         (VANG90 * 2)
#define VANG270         (VANG90 * 3)
#define VANG360         (VANG90 * 4)
#define MINDIST         (0x5800l)
#define FOCALLENGTH     (0x5800l)

#define NORTH   0
#define EAST    1
#define SOUTH   2
#define WEST    3
#define STATUSLINES 40
#define PIXRADIUS   512
#define STARTAMMO   8

/* object flags */
#define FL_SHOOTABLE    1
#define FL_BONUS        2
#define FL_NEVERMARK    4
#define FL_VISABLE      8
#define FL_ATTACKMODE   16
#define FL_FIRSTATTACK  32
#define FL_AMBUSH       64
#define FL_NONMARK      128

#define DOORWALL        98          /* first door wall page */

typedef enum { di_north, di_east, di_south, di_west } controldir_t;
typedef enum { dr_normal, dr_lock1, dr_lock2, dr_lock3, dr_lock4, dr_elevator } door_t;
typedef enum { ac_badobject = -1, ac_no, ac_yes, ac_allways } activetype;

typedef enum
{
    nothing, playerobj, inertobj, guardobj, officerobj, ssobj, dogobj,
    bossobj, schabbobj, fakeobj, mechahitlerobj, mutantobj, needleobj,
    fireobj, bjobj, ghostobj, realhitlerobj, gretelobj, giftobj, fatobj,
    rocketobj, spectreobj, angelobj, transobj, uberobj, willobj, deathobj,
    hrocketobj, sparkobj
} classtype;

typedef enum
{
    dressing, block, bo_gibs, bo_alpo, bo_firstaid, bo_key1, bo_key2,
    bo_key3, bo_key4, bo_cross, bo_chalice, bo_bible, bo_crown, bo_clip,
    bo_clip2, bo_machinegun, bo_chaingun, bo_food, bo_fullheal, bo_25clip,
    bo_spear
} stat_t;

typedef enum
{
    east, northeast, north, northwest, west, southwest, south, southeast, nodir
} dirtype;

typedef enum
{
    en_guard, en_officer, en_ss, en_dog, en_boss, en_schabbs, en_fake,
    en_hitler, en_mutant, en_blinky, en_clyde, en_pinky, en_inky, en_gretel,
    en_gift, en_fat, en_spectre, en_angel, en_trans, en_uber, en_will,
    en_death
} enemy_t;

struct objstruct;
typedef struct statestruct
{
    s16 rotate;
    s16 shapenum;               /* -1 = take from ob->temp1 */
    s16 tictime;
    void (*think)(struct objstruct *);
    void (*action)(struct objstruct *);
    const struct statestruct *next;
} statetype;

typedef struct
{
    u8 tilex, tiley;
    s16 shapenum;               /* -1 = removed */
    u8 flags;
    u8 itemnumber;
} statobj_t;

enum { dr_open, dr_closed, dr_opening, dr_closing };
typedef struct
{
    u8 tilex, tiley;
    u8 vertical;
    u8 lock;
    u8 action;
    s16 ticcount;
} doorobj_t;

typedef struct objstruct
{
    s8 active;
    s16 ticcount;
    u8 obclass;
    const statetype *state;
    u8 flags;
    s32 distance;
    u8 dir;
    s32 x, y;
    u16 tilex, tiley;
    u8 areanumber;
    s16 viewx;
    u16 viewheight;
    s32 transx;
    s16 angle;
    s16 hitpoints;
    s32 speed;
    s16 temp1, temp2, temp3;
    struct objstruct *next, *prev;
} objtype;

enum { bt_nobutton = -1, bt_attack = 0, bt_strafe, bt_run, bt_use,
       bt_readyknife, bt_readypistol, bt_readymachinegun, bt_readychaingun };
#define NUMBUTTONS 8

typedef enum { wp_knife, wp_pistol, wp_machinegun, wp_chaingun } weapontype;
enum { gd_baby, gd_easy, gd_medium, gd_hard };

typedef struct
{
    s16 difficulty;
    s16 mapon;
    s32 oldscore, score, nextextra;
    s16 lives;
    s16 health;
    s16 ammo;
    s16 keys;
    weapontype bestweapon, weapon, chosenweapon;
    s16 faceframe;
    s16 attackframe, attackcount, weaponframe;
    s16 episode, secretcount, treasurecount, killcount,
        secrettotal, treasuretotal, killtotal;
    s32 TimeCount;
    s32 killx, killy;
    boolean victoryflag;
} gametype;

typedef enum
{
    ex_stillplaying, ex_completed, ex_died, ex_warped, ex_resetgame,
    ex_loadedgame, ex_victorious, ex_abort, ex_demodone, ex_secretlevel
} exit_t;

/* ----------------------------------------------------------- globals */
extern gametype gamestate;
extern exit_t playstate;
extern boolean madenoise;
extern objtype objlist[MAXACTORS];
extern objtype *newobj, *player, *lastobj, *objfreelist, *killerobj;
extern statobj_t statobjlist[MAXSTATS], *laststatobj;
extern doorobj_t doorobjlist[MAXDOORS], *lastdoorobj;

extern u8 tilemap[MAPSIZE][MAPSIZE];
extern u8 screenbuf[32000];
/* per-frame scratch: lives in the unused tail of the video staging buffer */
#define spotvis (*(u8 (*)[MAPSIZE][MAPSIZE])(screenbuf + 22784))
extern u8 actorat[MAPSIZE][MAPSIZE];
/* actorat holds 0 (nothing), a wall/blocking value (1..0x3F), a door
 * (0x80|n) or an actor: 0x40|id for id<64, 0xC0|(id-64) for id>=64 */
extern u8 mapplane0[MAPSIZE * MAPSIZE];    /* area numbers / wall tiles (RAM copy) */
extern const u16 *mapplane1;               /* objects (ROM) */
#define MAPSPOT0(x, y)      (mapplane0[((y) << 6) + (x)])
#define MAPSPOT1(x, y)      (mapplane1[((y) << 6) + (x)])
#define ACT_ISACTOR(v)      ((v) & 0x40)
static inline u8 act_enc(const objtype *o)
{
    u8 id = (u8)(o - objlist);
    return 0x40 | (id & 0x3F) | ((id & 0x40) << 1);
}
static inline objtype *act_dec(u8 v)
{
    return (v & 0x40) ? &objlist[(v & 0x3F) | ((v & 0x80) >> 1)] : 0;
}
/* the actor standing at a tile, or NULL (also for walls and doors) */
#define ACTORAT(x, y)       act_dec(actorat[x][y])

extern s32 viewx, viewy;
extern s16 viewangle;
extern s32 viewsin, viewcos;
extern s16 centerx;
extern u16 wallheight[VIEWW / 2];
extern u16 pwallpos, pwallstate, pwallx, pwally;
extern s16 pwalldir;
extern u16 doorposition[MAXDOORS];
extern u8 areaconnect[NUMAREAS][NUMAREAS];
extern boolean areabyplayer[NUMAREAS];
extern const s16 dirangle[9];
extern s16 tics;
extern boolean loadedgame;

/* ---------------------------------------------------------- render.c */
void R_Init(void);
void R_SetLevelColors(u16 ceilcolor);
void R_Frame(void);                         /* ThreeDRefresh */
void ThreeDRefresh(void);
s32 FixedByFrac(s32 a, s32 b);
void TransformActor(objtype *ob);
boolean TransformTile(s16 tx, s16 ty, s16 *dispx, s16 *dispheight);
s16 CalcRotate(objtype *ob);
extern s16 weapon_spr;                      /* sprite drawn over the view, -1 = none */
extern s16 weapon_dy;

/* ----------------------------------------------------------- others */
#include "audionames.h"
#include "gfxnames.h"
#include "wl_proto.h"

#endif
