/* wl_proto.h - cross module declarations */
#ifndef WL_PROTO_H
#define WL_PROTO_H

#include "wl_states.h"
#include "snd.h"

#define UNSIGNEDSHIFT   8
#define costable        (&sintable[ANGLES / 4])
#define LABS(x)         ((s32)(x) > 0 ? (x) : -(x))
#define TURNTICS        10
#define SPDPATROL       512
#define SPDDOG          1500

/* main */
void Quit(const char *error);
u16 US_RndT(void);
void US_InitRndT(boolean randomize);

/* wl_act1 */
void InitDoorList(void);
void InitStaticList(void);
void SpawnStatic(s16 tilex, s16 tiley, s16 type);
void SpawnDoor(s16 tilex, s16 tiley, boolean vertical, s16 lock);
void MoveDoors(void);
void MovePWalls(void);
void OpenDoor(s16 door);
void PlaceItemType(s16 itemtype, s16 tilex, s16 tiley);
void PushWall(s16 checkx, s16 checky, s16 dir);
void OperateDoor(s16 door);
void InitAreas(void);
void ConnectAreas(void);
u16 InfoPlane(s16 x, s16 y);
extern u8 info_clr_x[], info_clr_y[], info_clr_n;
extern s16 doornum;

/* wl_state */
extern const dirtype opposite[9];
extern const dirtype diagonal[9][9];
void SpawnNewObj(u16 tilex, u16 tiley, const statetype *state);
void NewState(objtype *ob, const statetype *state);
boolean TryWalk(objtype *ob);
void SelectChaseDir(objtype *ob);
void SelectDodgeDir(objtype *ob);
void SelectRunDir(objtype *ob);
void MoveObj(objtype *ob, s32 move);
boolean SightPlayer(objtype *ob);
void KillActor(objtype *ob);
void DamageActor(objtype *ob, u16 damage);
boolean CheckLine(objtype *ob);
boolean CheckSight(objtype *ob);
void FirstSighting(objtype *ob);
void DropItem(stat_t itemtype, s16 tilex, s16 tiley);

/* wl_act2 */
void SpawnStand(enemy_t which, s16 tilex, s16 tiley, s16 dir);
void SpawnPatrol(enemy_t which, s16 tilex, s16 tiley, s16 dir);
void SpawnDeadGuard(s16 tilex, s16 tiley);
void SpawnBoss(s16 tilex, s16 tiley);
void SpawnGretel(s16 tilex, s16 tiley);
void SpawnGhosts(s16 which, s16 tilex, s16 tiley);
void SpawnSchabbs(s16 tilex, s16 tiley);
void SpawnGift(s16 tilex, s16 tiley);
void SpawnFat(s16 tilex, s16 tiley);
void SpawnFakeHitler(s16 tilex, s16 tiley);
void SpawnHitler(s16 tilex, s16 tiley);
void A_DeathScream(objtype *ob);
void A_StartDeathCam(objtype *ob);
s16 AimAngle(s32 dy, s32 dx);

/* wl_agent */
extern boolean running;
extern s32 thrustspeed;
extern u16 plux, pluy;
extern s16 anglefrac;
extern s16 facecount;
void SpawnPlayer(s16 tilex, s16 tiley, s16 dir);
void DrawFace(void);
void DrawStatusBar(void);
extern u16 border_pal[16];
void DrawHealth(void);
void TakeDamage(s16 points, objtype *attacker);
void HealSelf(s16 points);
void DrawLevel(void);
void DrawLives(void);
void GiveExtraMan(void);
void DrawScore(void);
void GivePoints(s32 points);
void DrawWeapon(void);
void DrawKeys(void);
void GiveWeapon(s16 weapon);
void DrawAmmo(void);
void GiveAmmo(s16 ammo);
void GiveKey(s16 key);
void GetBonus(statobj_t *check);
void Thrust(s16 angle, s32 speed);

/* wl_play */
extern u16 game_pal0[16];
void CalcTics(void);
void StartMusic(void);
void StopMusic(void);
extern boolean godmode, noclip;
extern boolean buttonstate[NUMBUTTONS];
extern s16 controlx, controly;
extern boolean singlestep;
extern boolean buttonheld[NUMBUTTONS];
extern s16 shootdelta;
void SpawnBJVictory(void);
void InitActorList(void);
void GetNewActor(void);
void RemoveObj(objtype *gone);
void PollControls(void);
void PlayLoop(void);
void StartDamageFlash(s16 damage);
void StartBonusFlash(void);
void FinishPaletteShifts(void);
void InitRedShifts(void);

/* wl_game */
void DeathCamIntro(void);
extern boolean fizzlein;
void SetupGameLevel(void);
void ScanInfoPlane(void);
void GameLoop(void);
void PlaySoundLocGlobal(u16 s, s32 gx, s32 gy);
void UpdateSoundLoc(void);
#define PlaySoundLocTile(s, tx, ty) \
    PlaySoundLocGlobal(s, (((s32)(tx) << TILESHIFT) + (1L << (TILESHIFT - 1))), (((s32)(ty) << TILESHIFT) + (1L << (TILESHIFT - 1))))
#define PlaySoundLocActor(s, ob)    PlaySoundLocGlobal(s, (ob)->x, (ob)->y)

#endif
