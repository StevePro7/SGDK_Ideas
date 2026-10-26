/* save.c - saved games and high scores in cartridge SRAM (32 KB, odd bytes) */
#include <genesis.h>
#include "wl_def.h"
#include "wl_proto.h"
#include "vid.h"
#include "save.h"
#include "inter.h"
#include <string.h>

extern u8 ratio_kill[8], ratio_secret[8], ratio_treasure[8];
extern u16 ratio_time[8];
extern void SetupGameLevel(void);

#define SRAM_MAGIC      0x5746      /* 'WF' */
#define HDR_SIZE        256
#define SLOT_SIZE       10240
#define SLOT_BASE(n)    (HDR_SIZE + (u32)(n) * SLOT_SIZE)
#define NAME_OFS        2

static u32 pos, limit;
static u16 sum;
static boolean overflow;

static void wb(u8 b)
{
    if (pos >= limit) { overflow = TRUE; return; }
    SRAM_writeByte(pos++, b);
    sum = (sum << 1 | sum >> 15) ^ b;
}

static u8 rb(void)
{
    u8 b;
    if (pos >= limit) { overflow = TRUE; return 0; }
    b = SRAM_readByte(pos++);
    sum = (sum << 1 | sum >> 15) ^ b;
    return b;
}

static void wmem(const void *p, u16 n)
{
    const u8 *s = p;
    while (n--) wb(*s++);
}

static void rmem(void *p, u16 n)
{
    u8 *d = p;
    while (n--) *d++ = rb();
}

static void wrle(const u8 *p, u16 n)
{
    u16 i = 0;
    while (i < n)
    {
        u8 v = p[i];
        u16 run = 1;
        while (i + run < n && p[i + run] == v && run < 255) run++;
        wb(run);
        wb(v);
        i += run;
    }
}

static void rrle(u8 *p, u16 n)
{
    u16 i = 0;
    while (i < n)
    {
        u8 run = rb(), v = rb();
        if (overflow || !run) return;
        while (run-- && i < n) p[i++] = v;
    }
}

/* ------------------------------------------------------------- scores */

void Scores_Load(void)
{
    u16 i;
    Scores_Defaults();
    SRAM_enableRO();
    if (SRAM_readWord(0) == SRAM_MAGIC)
    {
        u8 tmp[168];
        u16 s = 0;
        for (i = 0; i < Scores_Size(); i++)
        {
            tmp[i] = SRAM_readByte(4 + i);
            s = (s << 1 | s >> 15) ^ tmp[i];
        }
        if (s == SRAM_readWord(2))
            memcpy(Scores_Ptr(), tmp, Scores_Size());
    }
    SRAM_disable();
}

void Scores_Store(void)
{
    u16 i, s = 0;
    const u8 *p = Scores_Ptr();
    SRAM_enable();
    for (i = 0; i < Scores_Size(); i++)
    {
        SRAM_writeByte(4 + i, p[i]);
        s = (s << 1 | s >> 15) ^ p[i];
    }
    SRAM_writeWord(2, s);
    SRAM_writeWord(0, SRAM_MAGIC);
    SRAM_disable();
}

/* -------------------------------------------------------------- slots */

boolean Save_Used(s16 slot)
{
    boolean r;
    SRAM_enableRO();
    r = SRAM_readWord(SLOT_BASE(slot)) == SRAM_MAGIC;
    SRAM_disable();
    return r;
}

void Save_Name(s16 slot, char *out)
{
    u16 i;
    SRAM_enableRO();
    for (i = 0; i < SAVE_NAMELEN; i++)
        out[i] = SRAM_readByte(SLOT_BASE(slot) + NAME_OFS + i);
    out[SAVE_NAMELEN - 1] = 0;
    SRAM_disable();
}

boolean Save_Write(s16 slot, const char *name)
{
    u32 base = SLOT_BASE(slot);
    u16 i, n;
    objtype *o;
    char nm[SAVE_NAMELEN];

    memset(nm, 0, sizeof(nm));
    for (i = 0; i < SAVE_NAMELEN - 1 && name[i]; i++)
        nm[i] = name[i];

    SRAM_enable();
    SRAM_writeWord(base, 0);                    /* invalidate while writing */
    pos = base + NAME_OFS + SAVE_NAMELEN + 4;   /* checksum and length follow the name */
    limit = base + SLOT_SIZE;
    sum = 0;
    overflow = FALSE;

    wmem(&gamestate, sizeof(gamestate));
    wmem(ratio_kill, 8); wmem(ratio_secret, 8); wmem(ratio_treasure, 8);
    wmem(ratio_time, sizeof(ratio_time));
    wmem(&pwallstate, 2); wmem(&pwallpos, 2); wmem(&pwallx, 2); wmem(&pwally, 2); wmem(&pwalldir, 2);

    wrle(&tilemap[0][0], sizeof(tilemap));
    wrle(&actorat[0][0], sizeof(actorat));
    wrle(mapplane0, MAPSIZE * MAPSIZE);
    wmem(areaconnect, sizeof(areaconnect));
    wmem(areabyplayer, sizeof(areabyplayer));

    n = lastdoorobj - doorobjlist;
    wmem(&n, 2);
    wmem(doorobjlist, n * sizeof(doorobj_t));
    wmem(doorposition, n * 2);

    n = laststatobj - statobjlist;
    wmem(&n, 2);
    wmem(statobjlist, n * sizeof(statobj_t));

    n = 0;
    for (o = player; o; o = o->next) n++;
    wmem(&n, 2);
    for (o = player; o; o = o->next)
        wmem(o, sizeof(objtype));

    if (overflow)
    {
        SRAM_disable();
        return FALSE;
    }
    for (i = 0; i < SAVE_NAMELEN; i++)
        SRAM_writeByte(base + NAME_OFS + i, nm[i]);
    SRAM_writeWord(base + NAME_OFS + SAVE_NAMELEN, sum);
    SRAM_writeWord(base + NAME_OFS + SAVE_NAMELEN + 2, (u16)(pos - (base + NAME_OFS + SAVE_NAMELEN + 4)));
    SRAM_writeWord(base, SRAM_MAGIC);
    SRAM_disable();
    return TRUE;
}

boolean Save_Read(s16 slot)
{
    u32 base = SLOT_BASE(slot);
    u16 i, n, want;
    gametype gs;
    objtype tmp;
    u8 rk[8], rs[8], rt[8];
    u16 rtm[8], pw[5];

    /* verify the checksum first */
    SRAM_enableRO();
    pos = base + NAME_OFS + SAVE_NAMELEN + 4;
    limit = base + SLOT_SIZE;
    want = SRAM_readWord(base + NAME_OFS + SAVE_NAMELEN);
    n = SRAM_readWord(base + NAME_OFS + SAVE_NAMELEN + 2);
    sum = 0;
    overflow = FALSE;
    if (n > SLOT_SIZE)
        overflow = TRUE;
    for (i = 0; i < n && !overflow; i++)
        rb();
    if (overflow || sum != want)
    {
        SRAM_disable();
        return FALSE;
    }
    pos = base + NAME_OFS + SAVE_NAMELEN + 4;
    sum = 0;

    rmem(&gs, sizeof(gs));
    rmem(rk, 8); rmem(rs, 8); rmem(rt, 8);
    rmem(rtm, sizeof(rtm));
    for (i = 0; i < 5; i++) rmem(&pw[i], 2);
    if (overflow || gs.mapon < 0 || gs.mapon > 9)
    {
        SRAM_disable();
        return FALSE;
    }

    /* build the level, then overwrite everything dynamic */
    gamestate = gs;
    loadedgame = TRUE;
    SetupGameLevel();
    gamestate = gs;
    memcpy(ratio_kill, rk, 8); memcpy(ratio_secret, rs, 8); memcpy(ratio_treasure, rt, 8);
    memcpy(ratio_time, rtm, sizeof(rtm));
    pwallstate = pw[0]; pwallpos = pw[1]; pwallx = pw[2]; pwally = pw[3]; pwalldir = pw[4];

    rrle(&tilemap[0][0], sizeof(tilemap));
    rrle(&actorat[0][0], sizeof(actorat));
    rrle(mapplane0, MAPSIZE * MAPSIZE);
    rmem(areaconnect, sizeof(areaconnect));
    rmem(areabyplayer, sizeof(areabyplayer));

    rmem(&n, 2);
    if (n > MAXDOORS) n = 0;
    rmem(doorobjlist, n * sizeof(doorobj_t));
    rmem(doorposition, n * 2);
    lastdoorobj = &doorobjlist[n];

    rmem(&n, 2);
    if (n > MAXSTATS) n = 0;
    rmem(statobjlist, n * sizeof(statobj_t));
    laststatobj = &statobjlist[n];

    rmem(&n, 2);
    InitActorList();
    for (i = 0; i < n && !overflow; i++)
    {
        rmem(&tmp, sizeof(objtype));
        if (i == 0)
        {
            struct objstruct *nx = player->next, *pv = player->prev;
            *player = tmp;
            player->next = nx;
            player->prev = pv;
        }
        else
        {
            struct objstruct *nx, *pv;
            GetNewActor();
            nx = newobj->next;
            pv = newobj->prev;
            *newobj = tmp;
            newobj->next = nx;
            newobj->prev = pv;
        }
    }
    SRAM_disable();
    (void)want;
    return !overflow;
}
