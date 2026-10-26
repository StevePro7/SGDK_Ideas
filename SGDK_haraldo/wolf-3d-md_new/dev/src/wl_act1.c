/* wl_act1.c - statics, doors, pushable walls (port of WL_ACT1.C) */
#include "wl_def.h"
#include "snd.h"
#include <string.h>

statobj_t statobjlist[MAXSTATS], *laststatobj;

typedef struct
{
    s16 picnum;
    s8 type;
} statinfo_t;

static const statinfo_t statinfo[] =
{
    {SPR_STAT_0, dressing},
    {SPR_STAT_1, block},
    {SPR_STAT_2, block},
    {SPR_STAT_3, block},
    {SPR_STAT_4, dressing},
    {SPR_STAT_5, block},
    {SPR_STAT_6, bo_alpo},
    {SPR_STAT_7, block},
    {SPR_STAT_8, block},
    {SPR_STAT_9, dressing},
    {SPR_STAT_10, block},
    {SPR_STAT_11, block},
    {SPR_STAT_12, block},
    {SPR_STAT_13, block},
    {SPR_STAT_14, dressing},
    {SPR_STAT_15, dressing},
    {SPR_STAT_16, block},
    {SPR_STAT_17, block},
    {SPR_STAT_18, block},
    {SPR_STAT_19, dressing},
    {SPR_STAT_20, bo_key1},
    {SPR_STAT_21, bo_key2},
    {SPR_STAT_22, block},
    {SPR_STAT_23, dressing},
    {SPR_STAT_24, bo_food},
    {SPR_STAT_25, bo_firstaid},
    {SPR_STAT_26, bo_clip},
    {SPR_STAT_27, bo_machinegun},
    {SPR_STAT_28, bo_chaingun},
    {SPR_STAT_29, bo_cross},
    {SPR_STAT_30, bo_chalice},
    {SPR_STAT_31, bo_bible},
    {SPR_STAT_32, bo_crown},
    {SPR_STAT_33, bo_fullheal},
    {SPR_STAT_34, bo_gibs},
    {SPR_STAT_35, block},
    {SPR_STAT_36, block},
    {SPR_STAT_37, block},
    {SPR_STAT_38, bo_gibs},
    {SPR_STAT_39, block},
    {SPR_STAT_40, block},
    {SPR_STAT_41, dressing},
    {SPR_STAT_42, dressing},
    {SPR_STAT_43, dressing},
    {SPR_STAT_44, dressing},
    {SPR_STAT_45, block},
    {SPR_STAT_46, block},
    {SPR_STAT_47, dressing},
    {SPR_STAT_26, bo_clip2},
    {-1, 0}
};

/* The info plane lives in ROM; the few tiles the game clears at run time
 * (a pushed secret wall loses its marker) are remembered in a short list. */
#define MAXCLEARED 32
u8 info_clr_x[MAXCLEARED], info_clr_y[MAXCLEARED];
u8 info_clr_n;

u16 InfoPlane(s16 x, s16 y)
{
    u8 i;
    for (i = 0; i < info_clr_n; i++)
        if (info_clr_x[i] == x && info_clr_y[i] == y)
            return 0;
    return MAPSPOT1(x, y);
}

static void ClearInfo(s16 x, s16 y)
{
    if (info_clr_n < MAXCLEARED)
    {
        info_clr_x[info_clr_n] = x;
        info_clr_y[info_clr_n] = y;
        info_clr_n++;
    }
}

void InitStaticList(void)
{
    laststatobj = &statobjlist[0];
}

void SpawnStatic(s16 tilex, s16 tiley, s16 type)
{
    laststatobj->shapenum = statinfo[type].picnum;
    laststatobj->tilex = tilex;
    laststatobj->tiley = tiley;
    laststatobj->flags = 0;
    laststatobj->itemnumber = 0;

    switch (statinfo[type].type)
    {
    case block:
        actorat[tilex][tiley] = 1;      /* consider it a blocking tile */
    case dressing:
        laststatobj->flags = 0;
        break;

    case bo_cross:
    case bo_chalice:
    case bo_bible:
    case bo_crown:
    case bo_fullheal:
        if (!loadedgame)
            gamestate.treasuretotal++;
    case bo_firstaid:
    case bo_key1:
    case bo_key2:
    case bo_key3:
    case bo_key4:
    case bo_clip:
    case bo_25clip:
    case bo_machinegun:
    case bo_chaingun:
    case bo_food:
    case bo_alpo:
    case bo_gibs:
    case bo_spear:
        laststatobj->flags = FL_BONUS;
        laststatobj->itemnumber = statinfo[type].type;
        break;
    }

    laststatobj++;
    if (laststatobj == &statobjlist[MAXSTATS])
        Quit("Too many static objects!");
}

/* Called during game play to drop actors' items. */
void PlaceItemType(s16 itemtype, s16 tilex, s16 tiley)
{
    s16 type;
    statobj_t *spot;

    for (type = 0;; type++)
    {
        if (statinfo[type].picnum == -1)
            Quit("PlaceItemType: couldn't find type!");
        if (statinfo[type].type == itemtype)
            break;
    }

    for (spot = &statobjlist[0];; spot++)
    {
        if (spot == laststatobj)
        {
            if (spot == &statobjlist[MAXSTATS])
                return;
            laststatobj++;
            break;
        }
        if (spot->shapenum == -1)
            break;
    }

    spot->shapenum = statinfo[type].picnum;
    spot->tilex = tilex;
    spot->tiley = tiley;
    spot->flags = FL_BONUS;
    spot->itemnumber = statinfo[type].type;
}

/*
 * DOORS
 */
#define DOORWIDTH   0x7800
#define OPENTICS    300

doorobj_t doorobjlist[MAXDOORS], *lastdoorobj;
s16 doornum;
u16 doorposition[MAXDOORS];
u8 areaconnect[NUMAREAS][NUMAREAS];
boolean areabyplayer[NUMAREAS];

static void RecursiveConnect(s16 areanumber)
{
    s16 i;
    for (i = 0; i < NUMAREAS; i++)
    {
        if (areaconnect[areanumber][i] && !areabyplayer[i])
        {
            areabyplayer[i] = TRUE;
            RecursiveConnect(i);
        }
    }
}

void ConnectAreas(void)
{
    memset(areabyplayer, 0, sizeof(areabyplayer));
    areabyplayer[player->areanumber] = TRUE;
    RecursiveConnect(player->areanumber);
}

void InitAreas(void)
{
    memset(areabyplayer, 0, sizeof(areabyplayer));
    areabyplayer[player->areanumber] = TRUE;
}

void InitDoorList(void)
{
    memset(areabyplayer, 0, sizeof(areabyplayer));
    memset(areaconnect, 0, sizeof(areaconnect));
    lastdoorobj = &doorobjlist[0];
    doornum = 0;
}

void SpawnDoor(s16 tilex, s16 tiley, boolean vertical, s16 lock)
{
    u8 *map;

    if (doornum == 64)
        Quit("64+ doors on level!");

    doorposition[doornum] = 0;
    lastdoorobj->tilex = tilex;
    lastdoorobj->tiley = tiley;
    lastdoorobj->vertical = vertical;
    lastdoorobj->lock = lock;
    lastdoorobj->action = dr_closed;

    actorat[tilex][tiley] = doornum | 0x80;
    tilemap[tilex][tiley] = doornum | 0x80;
    map = &MAPSPOT0(tilex, tiley);
    if (vertical)
    {
        *map = *(map - 1);
        tilemap[tilex][tiley - 1] |= 0x40;
        tilemap[tilex][tiley + 1] |= 0x40;
    }
    else
    {
        *map = *(map - MAPSIZE);
        tilemap[tilex - 1][tiley] |= 0x40;
        tilemap[tilex + 1][tiley] |= 0x40;
    }

    doornum++;
    lastdoorobj++;
}

void OpenDoor(s16 door)
{
    if (doorobjlist[door].action == dr_open)
        doorobjlist[door].ticcount = 0;
    else
        doorobjlist[door].action = dr_opening;
}

static void CloseDoor(s16 door)
{
    s16 tilex, tiley, area;
    objtype *check;

    tilex = doorobjlist[door].tilex;
    tiley = doorobjlist[door].tiley;

    if (actorat[tilex][tiley])
        return;

    if (player->tilex == tilex && player->tiley == tiley)
        return;

    if (doorobjlist[door].vertical)
    {
        if (player->tiley == tiley)
        {
            if (((player->x + MINDIST) >> TILESHIFT) == tilex)
                return;
            if (((player->x - MINDIST) >> TILESHIFT) == tilex)
                return;
        }
        check = ACTORAT(tilex - 1, tiley);
        if (check && ((check->x + MINDIST) >> TILESHIFT) == tilex)
            return;
        check = ACTORAT(tilex + 1, tiley);
        if (check && ((check->x - MINDIST) >> TILESHIFT) == tilex)
            return;
    }
    else
    {
        if (player->tilex == tilex)
        {
            if (((player->y + MINDIST) >> TILESHIFT) == tiley)
                return;
            if (((player->y - MINDIST) >> TILESHIFT) == tiley)
                return;
        }
        check = ACTORAT(tilex, tiley - 1);
        if (check && ((check->y + MINDIST) >> TILESHIFT) == tiley)
            return;
        check = ACTORAT(tilex, tiley + 1);
        if (check && ((check->y - MINDIST) >> TILESHIFT) == tiley)
            return;
    }

    area = MAPSPOT0(doorobjlist[door].tilex, doorobjlist[door].tiley) - AREATILE;
    if (areabyplayer[area])
        PlaySoundLocTile(CLOSEDOORSND, doorobjlist[door].tilex, doorobjlist[door].tiley);

    doorobjlist[door].action = dr_closing;
    actorat[tilex][tiley] = door | 0x80;
}

void OperateDoor(s16 door)
{
    s16 lock = doorobjlist[door].lock;

    if (lock >= dr_lock1 && lock <= dr_lock4)
    {
        if (!(gamestate.keys & (1 << (lock - dr_lock1))))
        {
            SD_PlaySound(NOWAYSND);
            return;
        }
    }

    switch (doorobjlist[door].action)
    {
    case dr_closed:
    case dr_closing:
        OpenDoor(door);
        break;
    case dr_open:
    case dr_opening:
        CloseDoor(door);
        break;
    }
}

static void DoorOpen(s16 door)
{
    if ((doorobjlist[door].ticcount += tics) >= OPENTICS)
        CloseDoor(door);
}

static void DoorOpening(s16 door)
{
    s16 area1, area2;
    u8 *map;
    s32 position;

    position = doorposition[door];
    if (!position)
    {
        map = &MAPSPOT0(doorobjlist[door].tilex, doorobjlist[door].tiley);
        if (doorobjlist[door].vertical)
        {
            area1 = *(map + 1);
            area2 = *(map - 1);
        }
        else
        {
            area1 = *(map - MAPSIZE);
            area2 = *(map + MAPSIZE);
        }
        area1 -= AREATILE;
        area2 -= AREATILE;

        areaconnect[area1][area2]++;
        areaconnect[area2][area1]++;

        ConnectAreas();

        if (areabyplayer[area1])
            PlaySoundLocTile(OPENDOORSND, doorobjlist[door].tilex, doorobjlist[door].tiley);
    }

    position += (s32)tics << 10;
    if (position >= 0xffff)
    {
        position = 0xffff;
        doorobjlist[door].ticcount = 0;
        doorobjlist[door].action = dr_open;
        actorat[doorobjlist[door].tilex][doorobjlist[door].tiley] = 0;
    }

    doorposition[door] = position;
}

static void DoorClosing(s16 door)
{
    s16 area1, area2;
    u8 *map;
    s32 position;
    s16 tilex, tiley;

    tilex = doorobjlist[door].tilex;
    tiley = doorobjlist[door].tiley;

    if (actorat[tilex][tiley] != (door | 0x80)
        || (player->tilex == tilex && player->tiley == tiley))
    {
        OpenDoor(door);
        return;
    }

    position = doorposition[door];
    position -= (s32)tics << 10;
    if (position <= 0)
    {
        position = 0;
        doorobjlist[door].action = dr_closed;
        map = &MAPSPOT0(doorobjlist[door].tilex, doorobjlist[door].tiley);
        if (doorobjlist[door].vertical)
        {
            area1 = *(map + 1);
            area2 = *(map - 1);
        }
        else
        {
            area1 = *(map - MAPSIZE);
            area2 = *(map + MAPSIZE);
        }
        area1 -= AREATILE;
        area2 -= AREATILE;
        areaconnect[area1][area2]--;
        areaconnect[area2][area1]--;
        ConnectAreas();
    }

    doorposition[door] = position;
}

void MoveDoors(void)
{
    s16 door;

    if (gamestate.victoryflag)
        return;

    for (door = 0; door < doornum; door++)
        switch (doorobjlist[door].action)
        {
        case dr_open:
            DoorOpen(door);
            break;
        case dr_opening:
            DoorOpening(door);
            break;
        case dr_closing:
            DoorClosing(door);
            break;
        }
}

/*
 * PUSHABLE WALLS
 */
u16 pwallstate;
u16 pwallpos;
u16 pwallx, pwally;
s16 pwalldir;

void PushWall(s16 checkx, s16 checky, s16 dir)
{
    s16 oldtile;
    s16 nx = checkx, ny = checky;

    if (pwallstate)
        return;

    oldtile = tilemap[checkx][checky];
    if (!oldtile)
        return;

    switch (dir)
    {
    case di_north: ny--; break;
    case di_east:  nx++; break;
    case di_south: ny++; break;
    case di_west:  nx--; break;
    }
    if (actorat[nx][ny])
    {
        SD_PlaySound(NOWAYSND);
        return;
    }
    actorat[nx][ny] = oldtile & 0x3F;
    tilemap[nx][ny] = oldtile;

    gamestate.secretcount++;
    pwallx = checkx;
    pwally = checky;
    pwalldir = dir;
    pwallstate = 1;
    pwallpos = 0;
    tilemap[pwallx][pwally] |= 0xc0;
    ClearInfo(pwallx, pwally);          /* remove P tile info */
    SD_PlaySound(PUSHWALLSND);
}

void MovePWalls(void)
{
    s16 oldblock, oldtile;
    s16 nx, ny;

    if (!pwallstate)
        return;

    oldblock = pwallstate / 128;

    pwallstate += tics;

    if (pwallstate / 128 != oldblock)
    {
        oldtile = tilemap[pwallx][pwally] & 63;

        tilemap[pwallx][pwally] = 0;
        actorat[pwallx][pwally] = 0;
        MAPSPOT0(pwallx, pwally) = player->areanumber + AREATILE;

        if (pwallstate > 256)
        {
            pwallstate = 0;
            return;
        }
        else
        {
            switch (pwalldir)
            {
            case di_north: pwally--; nx = pwallx; ny = pwally - 1; break;
            case di_east:  pwallx++; nx = pwallx + 1; ny = pwally; break;
            case di_south: pwally++; nx = pwallx; ny = pwally + 1; break;
            default:       pwallx--; nx = pwallx - 1; ny = pwally; break;
            }
            if (actorat[nx][ny])
            {
                pwallstate = 0;
                return;
            }
            actorat[nx][ny] = oldtile;
            tilemap[nx][ny] = oldtile;
            tilemap[pwallx][pwally] = oldtile | 0xc0;
        }
    }

    pwallpos = (pwallstate / 2) & 63;
}
