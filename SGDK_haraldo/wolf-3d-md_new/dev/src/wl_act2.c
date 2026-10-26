// WL_ACT2.C

#include "wl_def.h"
#include "snd.h"
#include "vid.h"

/*
=============================================================================

						 LOCAL CONSTANTS

=============================================================================
*/

#define PROJECTILESIZE	0xc000l

#define BJRUNSPEED	2048
#define BJJUMPSPEED	680


/*
=============================================================================

						 GLOBAL VARIABLES

=============================================================================
*/



/*
=============================================================================

						 LOCAL VARIABLES

=============================================================================
*/


/* angle (0..ANGLES-1, counter clockwise, y up) of the vector (dx,dy) */
s16 AimAngle(s32 dy, s32 dx)
{
	u32 ax = dx < 0 ? -dx : dx, ay = dy < 0 ? -dy : dy;
	s16 f, lo, hi;
	u32 ratio;

	if (!ax && !ay)
		return 0;
	while (ax >= 32768 || ay >= 32768)
	{
		ax >>= 1;
		ay >>= 1;
	}
	if (ay <= ax)
	{
		ratio = (ay << 16) / ax;
		lo = 0; hi = ANG90 / 2;
		while (lo < hi)
		{
			s16 mid = (lo + hi) >> 1;
			if ((u32)finetangent[mid] < ratio) lo = mid + 1; else hi = mid;
		}
		f = lo;
	}
	else
	{
		ratio = (ax << 16) / ay;
		lo = 0; hi = ANG90 / 2;
		while (lo < hi)
		{
			s16 mid = (lo + hi) >> 1;
			if ((u32)finetangent[mid] < ratio) lo = mid + 1; else hi = mid;
		}
		f = ANG90 - 1 - lo;
	}
	if (dx < 0) f = ANG180 - 1 - f;
	if (dy < 0) f = FINEANGLES - 1 - f;
	if (f < 0) f = 0;
	return f / (FINEANGLES / ANGLES);
}

dirtype dirtable[9] = {northwest,north,northeast,west,nodir,east,
	southwest,south,southeast};

const s16 starthitpoints[4][NUMENEMIES] =
	 //
	 // BABY MODE
	 //
	 {
	 {25,	// guards
	  50,	// officer
	  100,	// SS
	  1,	// dogs
	  850,	// Hans
	  850,	// Schabbs
	  200,	// fake hitler
	  800,	// mecha hitler
	  45,	// mutants
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts

	  850,	// Gretel
	  850,	// Gift
	  850,	// Fat
	  5,	// en_spectre,
	  1450,	// en_angel,
	  850,	// en_trans,
	  1050,	// en_uber,
	  950,	// en_will,
	  1250	// en_death
	  },
	 //
	 // DON'T HURT ME MODE
	 //
	 {25,	// guards
	  50,	// officer
	  100,	// SS
	  1,	// dogs
	  950,	// Hans
	  950,	// Schabbs
	  300,	// fake hitler
	  950,	// mecha hitler
	  55,	// mutants
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts

	  950,	// Gretel
	  950,	// Gift
	  950,	// Fat
	  10,	// en_spectre,
	  1550,	// en_angel,
	  950,	// en_trans,
	  1150,	// en_uber,
	  1050,	// en_will,
	  1350	// en_death
	  },
	 //
	 // BRING 'EM ON MODE
	 //
	 {25,	// guards
	  50,	// officer
	  100,	// SS
	  1,	// dogs

	  1050,	// Hans
	  1550,	// Schabbs
	  400,	// fake hitler
	  1050,	// mecha hitler

	  55,	// mutants
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts

	  1050,	// Gretel
	  1050,	// Gift
	  1050,	// Fat
	  15,	// en_spectre,
	  1650,	// en_angel,
	  1050,	// en_trans,
	  1250,	// en_uber,
	  1150,	// en_will,
	  1450	// en_death
	  },
	 //
	 // DEATH INCARNATE MODE
	 //
	 {25,	// guards
	  50,	// officer
	  100,	// SS
	  1,	// dogs

	  1200,	// Hans
	  2400,	// Schabbs
	  500,	// fake hitler
	  1200,	// mecha hitler

	  65,	// mutants
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts
	  25,	// ghosts

	  1200,	// Gretel
	  1200,	// Gift
	  1200,	// Fat
	  25,	// en_spectre,
	  2000,	// en_angel,
	  1200,	// en_trans,
	  1400,	// en_uber,
	  1300,	// en_will,
	  1600	// en_death
	  }}
	  ;

void	A_StartDeathCam (objtype *ob);


void	T_Path (objtype *ob);
void	T_Shoot (objtype *ob);
void	T_Bite (objtype *ob);
void	T_DogChase (objtype *ob);
void	T_Chase (objtype *ob);
void	T_Projectile (objtype *ob);
void	T_Stand (objtype *ob);

void A_DeathScream (objtype *ob);

void A_Smoke (objtype *ob);

const statetype s_rocket = {TRUE,SPR_ROCKET_1,3,T_Projectile,A_Smoke,&s_rocket};
const statetype s_smoke1 = {FALSE,SPR_SMOKE_1,3,NULL,NULL,&s_smoke2};
const statetype s_smoke2 = {FALSE,SPR_SMOKE_2,3,NULL,NULL,&s_smoke3};
const statetype s_smoke3 = {FALSE,SPR_SMOKE_3,3,NULL,NULL,&s_smoke4};
const statetype s_smoke4 = {FALSE,SPR_SMOKE_4,3,NULL,NULL,NULL};

const statetype s_boom1 = {FALSE,SPR_BOOM_1,6,NULL,NULL,&s_boom2};
const statetype s_boom2 = {FALSE,SPR_BOOM_2,6,NULL,NULL,&s_boom3};
const statetype s_boom3 = {FALSE,SPR_BOOM_3,6,NULL,NULL,NULL};

#ifdef SPEAR

void A_Smoke (objtype *ob);

const statetype s_hrocket = {TRUE,SPR_HROCKET_1,3,T_Projectile,A_Smoke,&s_hrocket};
const statetype s_hsmoke1 = {FALSE,SPR_HSMOKE_1,3,NULL,NULL,&s_hsmoke2};
const statetype s_hsmoke2 = {FALSE,SPR_HSMOKE_2,3,NULL,NULL,&s_hsmoke3};
const statetype s_hsmoke3 = {FALSE,SPR_HSMOKE_3,3,NULL,NULL,&s_hsmoke4};
const statetype s_hsmoke4 = {FALSE,SPR_HSMOKE_4,3,NULL,NULL,NULL};

const statetype s_hboom1 = {FALSE,SPR_HBOOM_1,6,NULL,NULL,&s_hboom2};
const statetype s_hboom2 = {FALSE,SPR_HBOOM_2,6,NULL,NULL,&s_hboom3};
const statetype s_hboom3 = {FALSE,SPR_HBOOM_3,6,NULL,NULL,NULL};

#endif

void	T_Schabb (objtype *ob);
void	T_SchabbThrow (objtype *ob);
void	T_Fake (objtype *ob);
void	T_FakeFire (objtype *ob);
void	T_Ghosts (objtype *ob);

void A_Slurpie (objtype *ob);
void A_HitlerMorph (objtype *ob);
void A_MechaSound (objtype *ob);

/*
=================
=
= A_Smoke
=
=================
*/

void A_Smoke (objtype *ob)
{
	GetNewActor ();
#ifdef SPEAR
	if (ob->obclass == hrocketobj)
		newobj->state = &s_hsmoke1;
	else
#endif
		newobj->state = &s_smoke1;
	newobj->ticcount = 6;

	newobj->tilex = ob->tilex;
	newobj->tiley = ob->tiley;
	newobj->x = ob->x;
	newobj->y = ob->y;
	newobj->obclass = inertobj;
	newobj->active = TRUE;

	newobj->flags = FL_NEVERMARK;
}


/*
===================
=
= ProjectileTryMove
=
= returns TRUE if move ok
===================
*/

#define PROJSIZE	0x2000

boolean ProjectileTryMove (objtype *ob)
{
	s16			xl,yl,xh,yh,x,y;
	objtype		*check;
	s32		deltax,deltay;

	xl = (ob->x-PROJSIZE) >>TILESHIFT;
	yl = (ob->y-PROJSIZE) >>TILESHIFT;

	xh = (ob->x+PROJSIZE) >>TILESHIFT;
	yh = (ob->y+PROJSIZE) >>TILESHIFT;

//
// check for solid walls
//
	for (y=yl;y<=yh;y++)
		for (x=xl;x<=xh;x++)
		{
			u8 a = actorat[x][y];
			if (a && !ACT_ISACTOR(a))
				return FALSE;
		}

	return TRUE;
}



/*
=================
=
= T_Projectile
=
=================
*/

void T_Projectile (objtype *ob)
{
	s32	deltax,deltay;
	s16		damage;
	s32	speed;

	speed = (s32)ob->speed*tics;

	deltax = FixedByFrac(speed,costable[ob->angle]);
	deltay = -FixedByFrac(speed,sintable[ob->angle]);

	if (deltax>0x10000l)
		deltax = 0x10000l;
	if (deltay>0x10000l)
		deltay = 0x10000l;

	ob->x += deltax;
	ob->y += deltay;

	deltax = LABS(ob->x - player->x);
	deltay = LABS(ob->y - player->y);

	if (!ProjectileTryMove (ob))
	{
		if (ob->obclass == rocketobj)
		{
			PlaySoundLocActor(MISSILEHITSND,ob);
			ob->state = &s_boom1;
		}
#ifdef SPEAR
		else if (ob->obclass == hrocketobj)
		{
			PlaySoundLocActor(MISSILEHITSND,ob);
			ob->state = &s_hboom1;
		}
#endif
		else
			ob->state = NULL;		// mark for removal

		return;
	}

	if (deltax < PROJECTILESIZE && deltay < PROJECTILESIZE)
	{	// hit the player
		switch (ob->obclass)
		{
		case needleobj:
			damage = (US_RndT() >>3) + 20;
			break;
		case rocketobj:
		case hrocketobj:
		case sparkobj:
			damage = (US_RndT() >>3) + 30;
			break;
		case fireobj:
			damage = (US_RndT() >>3);
			break;
		}

		TakeDamage (damage,ob);
		ob->state = NULL;		// mark for removal
		return;
	}

	ob->tilex = ob->x >> TILESHIFT;
	ob->tiley = ob->y >> TILESHIFT;

}




/*
=============================================================================

							GUARD

=============================================================================
*/

//
// guards
//

const statetype s_grdstand = {TRUE,SPR_GRD_S_1,0,T_Stand,NULL,&s_grdstand};

const statetype s_grdpath1 = {TRUE,SPR_GRD_W1_1,20,T_Path,NULL,&s_grdpath1s};
const statetype s_grdpath1s = {TRUE,SPR_GRD_W1_1,5,NULL,NULL,&s_grdpath2};
const statetype s_grdpath2 = {TRUE,SPR_GRD_W2_1,15,T_Path,NULL,&s_grdpath3};
const statetype s_grdpath3 = {TRUE,SPR_GRD_W3_1,20,T_Path,NULL,&s_grdpath3s};
const statetype s_grdpath3s = {TRUE,SPR_GRD_W3_1,5,NULL,NULL,&s_grdpath4};
const statetype s_grdpath4 = {TRUE,SPR_GRD_W4_1,15,T_Path,NULL,&s_grdpath1};

const statetype s_grdpain = {2,SPR_GRD_PAIN_1,10,NULL,NULL,&s_grdchase1};
const statetype s_grdpain1 = {2,SPR_GRD_PAIN_2,10,NULL,NULL,&s_grdchase1};

const statetype s_grdshoot1 = {FALSE,SPR_GRD_SHOOT1,20,NULL,NULL,&s_grdshoot2};
const statetype s_grdshoot2 = {FALSE,SPR_GRD_SHOOT2,20,NULL,T_Shoot,&s_grdshoot3};
const statetype s_grdshoot3 = {FALSE,SPR_GRD_SHOOT3,20,NULL,NULL,&s_grdchase1};

const statetype s_grdchase1 = {TRUE,SPR_GRD_W1_1,10,T_Chase,NULL,&s_grdchase1s};
const statetype s_grdchase1s = {TRUE,SPR_GRD_W1_1,3,NULL,NULL,&s_grdchase2};
const statetype s_grdchase2 = {TRUE,SPR_GRD_W2_1,8,T_Chase,NULL,&s_grdchase3};
const statetype s_grdchase3 = {TRUE,SPR_GRD_W3_1,10,T_Chase,NULL,&s_grdchase3s};
const statetype s_grdchase3s = {TRUE,SPR_GRD_W3_1,3,NULL,NULL,&s_grdchase4};
const statetype s_grdchase4 = {TRUE,SPR_GRD_W4_1,8,T_Chase,NULL,&s_grdchase1};

const statetype s_grddie1 = {FALSE,SPR_GRD_DIE_1,15,NULL,A_DeathScream,&s_grddie2};
const statetype s_grddie2 = {FALSE,SPR_GRD_DIE_2,15,NULL,NULL,&s_grddie3};
const statetype s_grddie3 = {FALSE,SPR_GRD_DIE_3,15,NULL,NULL,&s_grddie4};
const statetype s_grddie4 = {FALSE,SPR_GRD_DEAD,0,NULL,NULL,&s_grddie4};


#ifndef SPEAR
//
// ghosts
//
const statetype s_blinkychase1 = {FALSE,SPR_BLINKY_W1,10,T_Ghosts,NULL,&s_blinkychase2};
const statetype s_blinkychase2 = {FALSE,SPR_BLINKY_W2,10,T_Ghosts,NULL,&s_blinkychase1};

const statetype s_inkychase1 = {FALSE,SPR_INKY_W1,10,T_Ghosts,NULL,&s_inkychase2};
const statetype s_inkychase2 = {FALSE,SPR_INKY_W2,10,T_Ghosts,NULL,&s_inkychase1};

const statetype s_pinkychase1 = {FALSE,SPR_PINKY_W1,10,T_Ghosts,NULL,&s_pinkychase2};
const statetype s_pinkychase2 = {FALSE,SPR_PINKY_W2,10,T_Ghosts,NULL,&s_pinkychase1};

const statetype s_clydechase1 = {FALSE,SPR_CLYDE_W1,10,T_Ghosts,NULL,&s_clydechase2};
const statetype s_clydechase2 = {FALSE,SPR_CLYDE_W2,10,T_Ghosts,NULL,&s_clydechase1};
#endif

//
// dogs
//

const statetype s_dogpath1 = {TRUE,SPR_DOG_W1_1,20,T_Path,NULL,&s_dogpath1s};
const statetype s_dogpath1s = {TRUE,SPR_DOG_W1_1,5,NULL,NULL,&s_dogpath2};
const statetype s_dogpath2 = {TRUE,SPR_DOG_W2_1,15,T_Path,NULL,&s_dogpath3};
const statetype s_dogpath3 = {TRUE,SPR_DOG_W3_1,20,T_Path,NULL,&s_dogpath3s};
const statetype s_dogpath3s = {TRUE,SPR_DOG_W3_1,5,NULL,NULL,&s_dogpath4};
const statetype s_dogpath4 = {TRUE,SPR_DOG_W4_1,15,T_Path,NULL,&s_dogpath1};

const statetype s_dogjump1 = {FALSE,SPR_DOG_JUMP1,10,NULL,NULL,&s_dogjump2};
const statetype s_dogjump2 = {FALSE,SPR_DOG_JUMP2,10,NULL,T_Bite,&s_dogjump3};
const statetype s_dogjump3 = {FALSE,SPR_DOG_JUMP3,10,NULL,NULL,&s_dogjump4};
const statetype s_dogjump4 = {FALSE,SPR_DOG_JUMP1,10,NULL,NULL,&s_dogjump5};
const statetype s_dogjump5 = {FALSE,SPR_DOG_W1_1,10,NULL,NULL,&s_dogchase1};

const statetype s_dogchase1 = {TRUE,SPR_DOG_W1_1,10,T_DogChase,NULL,&s_dogchase1s};
const statetype s_dogchase1s = {TRUE,SPR_DOG_W1_1,3,NULL,NULL,&s_dogchase2};
const statetype s_dogchase2 = {TRUE,SPR_DOG_W2_1,8,T_DogChase,NULL,&s_dogchase3};
const statetype s_dogchase3 = {TRUE,SPR_DOG_W3_1,10,T_DogChase,NULL,&s_dogchase3s};
const statetype s_dogchase3s = {TRUE,SPR_DOG_W3_1,3,NULL,NULL,&s_dogchase4};
const statetype s_dogchase4 = {TRUE,SPR_DOG_W4_1,8,T_DogChase,NULL,&s_dogchase1};

const statetype s_dogdie1 = {FALSE,SPR_DOG_DIE_1,15,NULL,A_DeathScream,&s_dogdie2};
const statetype s_dogdie2 = {FALSE,SPR_DOG_DIE_2,15,NULL,NULL,&s_dogdie3};
const statetype s_dogdie3 = {FALSE,SPR_DOG_DIE_3,15,NULL,NULL,&s_dogdead};
const statetype s_dogdead = {FALSE,SPR_DOG_DEAD,15,NULL,NULL,&s_dogdead};


//
// officers
//

const statetype s_ofcstand = {TRUE,SPR_OFC_S_1,0,T_Stand,NULL,&s_ofcstand};

const statetype s_ofcpath1 = {TRUE,SPR_OFC_W1_1,20,T_Path,NULL,&s_ofcpath1s};
const statetype s_ofcpath1s = {TRUE,SPR_OFC_W1_1,5,NULL,NULL,&s_ofcpath2};
const statetype s_ofcpath2 = {TRUE,SPR_OFC_W2_1,15,T_Path,NULL,&s_ofcpath3};
const statetype s_ofcpath3 = {TRUE,SPR_OFC_W3_1,20,T_Path,NULL,&s_ofcpath3s};
const statetype s_ofcpath3s = {TRUE,SPR_OFC_W3_1,5,NULL,NULL,&s_ofcpath4};
const statetype s_ofcpath4 = {TRUE,SPR_OFC_W4_1,15,T_Path,NULL,&s_ofcpath1};

const statetype s_ofcpain = {2,SPR_OFC_PAIN_1,10,NULL,NULL,&s_ofcchase1};
const statetype s_ofcpain1 = {2,SPR_OFC_PAIN_2,10,NULL,NULL,&s_ofcchase1};

const statetype s_ofcshoot1 = {FALSE,SPR_OFC_SHOOT1,6,NULL,NULL,&s_ofcshoot2};
const statetype s_ofcshoot2 = {FALSE,SPR_OFC_SHOOT2,20,NULL,T_Shoot,&s_ofcshoot3};
const statetype s_ofcshoot3 = {FALSE,SPR_OFC_SHOOT3,10,NULL,NULL,&s_ofcchase1};

const statetype s_ofcchase1 = {TRUE,SPR_OFC_W1_1,10,T_Chase,NULL,&s_ofcchase1s};
const statetype s_ofcchase1s = {TRUE,SPR_OFC_W1_1,3,NULL,NULL,&s_ofcchase2};
const statetype s_ofcchase2 = {TRUE,SPR_OFC_W2_1,8,T_Chase,NULL,&s_ofcchase3};
const statetype s_ofcchase3 = {TRUE,SPR_OFC_W3_1,10,T_Chase,NULL,&s_ofcchase3s};
const statetype s_ofcchase3s = {TRUE,SPR_OFC_W3_1,3,NULL,NULL,&s_ofcchase4};
const statetype s_ofcchase4 = {TRUE,SPR_OFC_W4_1,8,T_Chase,NULL,&s_ofcchase1};

const statetype s_ofcdie1 = {FALSE,SPR_OFC_DIE_1,11,NULL,A_DeathScream,&s_ofcdie2};
const statetype s_ofcdie2 = {FALSE,SPR_OFC_DIE_2,11,NULL,NULL,&s_ofcdie3};
const statetype s_ofcdie3 = {FALSE,SPR_OFC_DIE_3,11,NULL,NULL,&s_ofcdie4};
const statetype s_ofcdie4 = {FALSE,SPR_OFC_DIE_4,11,NULL,NULL,&s_ofcdie5};
const statetype s_ofcdie5 = {FALSE,SPR_OFC_DEAD,0,NULL,NULL,&s_ofcdie5};


//
// mutant
//

const statetype s_mutstand = {TRUE,SPR_MUT_S_1,0,T_Stand,NULL,&s_mutstand};

const statetype s_mutpath1 = {TRUE,SPR_MUT_W1_1,20,T_Path,NULL,&s_mutpath1s};
const statetype s_mutpath1s = {TRUE,SPR_MUT_W1_1,5,NULL,NULL,&s_mutpath2};
const statetype s_mutpath2 = {TRUE,SPR_MUT_W2_1,15,T_Path,NULL,&s_mutpath3};
const statetype s_mutpath3 = {TRUE,SPR_MUT_W3_1,20,T_Path,NULL,&s_mutpath3s};
const statetype s_mutpath3s = {TRUE,SPR_MUT_W3_1,5,NULL,NULL,&s_mutpath4};
const statetype s_mutpath4 = {TRUE,SPR_MUT_W4_1,15,T_Path,NULL,&s_mutpath1};

const statetype s_mutpain = {2,SPR_MUT_PAIN_1,10,NULL,NULL,&s_mutchase1};
const statetype s_mutpain1 = {2,SPR_MUT_PAIN_2,10,NULL,NULL,&s_mutchase1};

const statetype s_mutshoot1 = {FALSE,SPR_MUT_SHOOT1,6,NULL,T_Shoot,&s_mutshoot2};
const statetype s_mutshoot2 = {FALSE,SPR_MUT_SHOOT2,20,NULL,NULL,&s_mutshoot3};
const statetype s_mutshoot3 = {FALSE,SPR_MUT_SHOOT3,10,NULL,T_Shoot,&s_mutshoot4};
const statetype s_mutshoot4 = {FALSE,SPR_MUT_SHOOT4,20,NULL,NULL,&s_mutchase1};

const statetype s_mutchase1 = {TRUE,SPR_MUT_W1_1,10,T_Chase,NULL,&s_mutchase1s};
const statetype s_mutchase1s = {TRUE,SPR_MUT_W1_1,3,NULL,NULL,&s_mutchase2};
const statetype s_mutchase2 = {TRUE,SPR_MUT_W2_1,8,T_Chase,NULL,&s_mutchase3};
const statetype s_mutchase3 = {TRUE,SPR_MUT_W3_1,10,T_Chase,NULL,&s_mutchase3s};
const statetype s_mutchase3s = {TRUE,SPR_MUT_W3_1,3,NULL,NULL,&s_mutchase4};
const statetype s_mutchase4 = {TRUE,SPR_MUT_W4_1,8,T_Chase,NULL,&s_mutchase1};

const statetype s_mutdie1 = {FALSE,SPR_MUT_DIE_1,7,NULL,A_DeathScream,&s_mutdie2};
const statetype s_mutdie2 = {FALSE,SPR_MUT_DIE_2,7,NULL,NULL,&s_mutdie3};
const statetype s_mutdie3 = {FALSE,SPR_MUT_DIE_3,7,NULL,NULL,&s_mutdie4};
const statetype s_mutdie4 = {FALSE,SPR_MUT_DIE_4,7,NULL,NULL,&s_mutdie5};
const statetype s_mutdie5 = {FALSE,SPR_MUT_DEAD,0,NULL,NULL,&s_mutdie5};


//
// SS
//

const statetype s_ssstand = {TRUE,SPR_SS_S_1,0,T_Stand,NULL,&s_ssstand};

const statetype s_sspath1 = {TRUE,SPR_SS_W1_1,20,T_Path,NULL,&s_sspath1s};
const statetype s_sspath1s = {TRUE,SPR_SS_W1_1,5,NULL,NULL,&s_sspath2};
const statetype s_sspath2 = {TRUE,SPR_SS_W2_1,15,T_Path,NULL,&s_sspath3};
const statetype s_sspath3 = {TRUE,SPR_SS_W3_1,20,T_Path,NULL,&s_sspath3s};
const statetype s_sspath3s = {TRUE,SPR_SS_W3_1,5,NULL,NULL,&s_sspath4};
const statetype s_sspath4 = {TRUE,SPR_SS_W4_1,15,T_Path,NULL,&s_sspath1};

const statetype s_sspain = {2,SPR_SS_PAIN_1,10,NULL,NULL,&s_sschase1};
const statetype s_sspain1 = {2,SPR_SS_PAIN_2,10,NULL,NULL,&s_sschase1};

const statetype s_ssshoot1 = {FALSE,SPR_SS_SHOOT1,20,NULL,NULL,&s_ssshoot2};
const statetype s_ssshoot2 = {FALSE,SPR_SS_SHOOT2,20,NULL,T_Shoot,&s_ssshoot3};
const statetype s_ssshoot3 = {FALSE,SPR_SS_SHOOT3,10,NULL,NULL,&s_ssshoot4};
const statetype s_ssshoot4 = {FALSE,SPR_SS_SHOOT2,10,NULL,T_Shoot,&s_ssshoot5};
const statetype s_ssshoot5 = {FALSE,SPR_SS_SHOOT3,10,NULL,NULL,&s_ssshoot6};
const statetype s_ssshoot6 = {FALSE,SPR_SS_SHOOT2,10,NULL,T_Shoot,&s_ssshoot7};
const statetype s_ssshoot7 = {FALSE,SPR_SS_SHOOT3,10,NULL,NULL,&s_ssshoot8};
const statetype s_ssshoot8 = {FALSE,SPR_SS_SHOOT2,10,NULL,T_Shoot,&s_ssshoot9};
const statetype s_ssshoot9 = {FALSE,SPR_SS_SHOOT3,10,NULL,NULL,&s_sschase1};

const statetype s_sschase1 = {TRUE,SPR_SS_W1_1,10,T_Chase,NULL,&s_sschase1s};
const statetype s_sschase1s = {TRUE,SPR_SS_W1_1,3,NULL,NULL,&s_sschase2};
const statetype s_sschase2 = {TRUE,SPR_SS_W2_1,8,T_Chase,NULL,&s_sschase3};
const statetype s_sschase3 = {TRUE,SPR_SS_W3_1,10,T_Chase,NULL,&s_sschase3s};
const statetype s_sschase3s = {TRUE,SPR_SS_W3_1,3,NULL,NULL,&s_sschase4};
const statetype s_sschase4 = {TRUE,SPR_SS_W4_1,8,T_Chase,NULL,&s_sschase1};

const statetype s_ssdie1 = {FALSE,SPR_SS_DIE_1,15,NULL,A_DeathScream,&s_ssdie2};
const statetype s_ssdie2 = {FALSE,SPR_SS_DIE_2,15,NULL,NULL,&s_ssdie3};
const statetype s_ssdie3 = {FALSE,SPR_SS_DIE_3,15,NULL,NULL,&s_ssdie4};
const statetype s_ssdie4 = {FALSE,SPR_SS_DEAD,0,NULL,NULL,&s_ssdie4};


#ifndef SPEAR
//
// hans
//
const statetype s_bossstand = {FALSE,SPR_BOSS_W1,0,T_Stand,NULL,&s_bossstand};

const statetype s_bosschase1 = {FALSE,SPR_BOSS_W1,10,T_Chase,NULL,&s_bosschase1s};
const statetype s_bosschase1s = {FALSE,SPR_BOSS_W1,3,NULL,NULL,&s_bosschase2};
const statetype s_bosschase2 = {FALSE,SPR_BOSS_W2,8,T_Chase,NULL,&s_bosschase3};
const statetype s_bosschase3 = {FALSE,SPR_BOSS_W3,10,T_Chase,NULL,&s_bosschase3s};
const statetype s_bosschase3s = {FALSE,SPR_BOSS_W3,3,NULL,NULL,&s_bosschase4};
const statetype s_bosschase4 = {FALSE,SPR_BOSS_W4,8,T_Chase,NULL,&s_bosschase1};

const statetype s_bossdie1 = {FALSE,SPR_BOSS_DIE1,15,NULL,A_DeathScream,&s_bossdie2};
const statetype s_bossdie2 = {FALSE,SPR_BOSS_DIE2,15,NULL,NULL,&s_bossdie3};
const statetype s_bossdie3 = {FALSE,SPR_BOSS_DIE3,15,NULL,NULL,&s_bossdie4};
const statetype s_bossdie4 = {FALSE,SPR_BOSS_DEAD,0,NULL,NULL,&s_bossdie4};

const statetype s_bossshoot1 = {FALSE,SPR_BOSS_SHOOT1,30,NULL,NULL,&s_bossshoot2};
const statetype s_bossshoot2 = {FALSE,SPR_BOSS_SHOOT2,10,NULL,T_Shoot,&s_bossshoot3};
const statetype s_bossshoot3 = {FALSE,SPR_BOSS_SHOOT3,10,NULL,T_Shoot,&s_bossshoot4};
const statetype s_bossshoot4 = {FALSE,SPR_BOSS_SHOOT2,10,NULL,T_Shoot,&s_bossshoot5};
const statetype s_bossshoot5 = {FALSE,SPR_BOSS_SHOOT3,10,NULL,T_Shoot,&s_bossshoot6};
const statetype s_bossshoot6 = {FALSE,SPR_BOSS_SHOOT2,10,NULL,T_Shoot,&s_bossshoot7};
const statetype s_bossshoot7 = {FALSE,SPR_BOSS_SHOOT3,10,NULL,T_Shoot,&s_bossshoot8};
const statetype s_bossshoot8 = {FALSE,SPR_BOSS_SHOOT1,10,NULL,NULL,&s_bosschase1};


//
// gretel
//
const statetype s_gretelstand = {FALSE,SPR_GRETEL_W1,0,T_Stand,NULL,&s_gretelstand};

const statetype s_gretelchase1 = {FALSE,SPR_GRETEL_W1,10,T_Chase,NULL,&s_gretelchase1s};
const statetype s_gretelchase1s = {FALSE,SPR_GRETEL_W1,3,NULL,NULL,&s_gretelchase2};
const statetype s_gretelchase2 = {FALSE,SPR_GRETEL_W2,8,T_Chase,NULL,&s_gretelchase3};
const statetype s_gretelchase3 = {FALSE,SPR_GRETEL_W3,10,T_Chase,NULL,&s_gretelchase3s};
const statetype s_gretelchase3s = {FALSE,SPR_GRETEL_W3,3,NULL,NULL,&s_gretelchase4};
const statetype s_gretelchase4 = {FALSE,SPR_GRETEL_W4,8,T_Chase,NULL,&s_gretelchase1};

const statetype s_greteldie1 = {FALSE,SPR_GRETEL_DIE1,15,NULL,A_DeathScream,&s_greteldie2};
const statetype s_greteldie2 = {FALSE,SPR_GRETEL_DIE2,15,NULL,NULL,&s_greteldie3};
const statetype s_greteldie3 = {FALSE,SPR_GRETEL_DIE3,15,NULL,NULL,&s_greteldie4};
const statetype s_greteldie4 = {FALSE,SPR_GRETEL_DEAD,0,NULL,NULL,&s_greteldie4};

const statetype s_gretelshoot1 = {FALSE,SPR_GRETEL_SHOOT1,30,NULL,NULL,&s_gretelshoot2};
const statetype s_gretelshoot2 = {FALSE,SPR_GRETEL_SHOOT2,10,NULL,T_Shoot,&s_gretelshoot3};
const statetype s_gretelshoot3 = {FALSE,SPR_GRETEL_SHOOT3,10,NULL,T_Shoot,&s_gretelshoot4};
const statetype s_gretelshoot4 = {FALSE,SPR_GRETEL_SHOOT2,10,NULL,T_Shoot,&s_gretelshoot5};
const statetype s_gretelshoot5 = {FALSE,SPR_GRETEL_SHOOT3,10,NULL,T_Shoot,&s_gretelshoot6};
const statetype s_gretelshoot6 = {FALSE,SPR_GRETEL_SHOOT2,10,NULL,T_Shoot,&s_gretelshoot7};
const statetype s_gretelshoot7 = {FALSE,SPR_GRETEL_SHOOT3,10,NULL,T_Shoot,&s_gretelshoot8};
const statetype s_gretelshoot8 = {FALSE,SPR_GRETEL_SHOOT1,10,NULL,NULL,&s_gretelchase1};
#endif


/*
===============
=
= SpawnStand
=
===============
*/

void SpawnStand (enemy_t which, s16 tilex, s16 tiley, s16 dir)
{
	u8 *map;
	u16 tile;

	switch (which)
	{
	case en_guard:
		SpawnNewObj (tilex,tiley,&s_grdstand);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_officer:
		SpawnNewObj (tilex,tiley,&s_ofcstand);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_mutant:
		SpawnNewObj (tilex,tiley,&s_mutstand);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_ss:
		SpawnNewObj (tilex,tiley,&s_ssstand);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;
	}


	map = &MAPSPOT0(tilex, tiley);
	if (*map == AMBUSHTILE)
	{
		tilemap[tilex][tiley] = 0;

		if (*(map+1) >= AREATILE)
			tile = *(map+1);
		if (*(map-MAPSIZE) >= AREATILE)
			tile = *(map-MAPSIZE);
		if (*(map+MAPSIZE) >= AREATILE)
			tile = *(map+MAPSIZE);
		if ( *(map-1) >= AREATILE)
			tile = *(map-1);

		*map = tile;
		newobj->areanumber = tile-AREATILE;

		newobj->flags |= FL_AMBUSH;
	}

	newobj->obclass = guardobj+which;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][which];
	newobj->dir = dir*2;
	newobj->flags |= FL_SHOOTABLE;
}



/*
===============
=
= SpawnDeadGuard
=
===============
*/

void SpawnDeadGuard (s16 tilex, s16 tiley)
{
	SpawnNewObj (tilex,tiley,&s_grddie4);
	newobj->obclass = inertobj;
}



#ifndef SPEAR
/*
===============
=
= SpawnBoss
=
===============
*/

void SpawnBoss (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	SpawnNewObj (tilex,tiley,&s_bossstand);
	newobj->speed = SPDPATROL;

	newobj->obclass = bossobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_boss];
	newobj->dir = south;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}

/*
===============
=
= SpawnGretel
=
===============
*/

void SpawnGretel (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	SpawnNewObj (tilex,tiley,&s_gretelstand);
	newobj->speed = SPDPATROL;

	newobj->obclass = gretelobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_gretel];
	newobj->dir = north;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}
#endif

/*
===============
=
= SpawnPatrol
=
===============
*/

void SpawnPatrol (enemy_t which, s16 tilex, s16 tiley, s16 dir)
{
	switch (which)
	{
	case en_guard:
		SpawnNewObj (tilex,tiley,&s_grdpath1);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_officer:
		SpawnNewObj (tilex,tiley,&s_ofcpath1);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_ss:
		SpawnNewObj (tilex,tiley,&s_sspath1);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_mutant:
		SpawnNewObj (tilex,tiley,&s_mutpath1);
		newobj->speed = SPDPATROL;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;

	case en_dog:
		SpawnNewObj (tilex,tiley,&s_dogpath1);
		newobj->speed = SPDDOG;
		if (!loadedgame)
		  gamestate.killtotal++;
		break;
	}

	newobj->obclass = guardobj+which;
	newobj->dir = dir*2;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][which];
	newobj->distance = TILEGLOBAL;
	newobj->flags |= FL_SHOOTABLE;
	newobj->active = TRUE;

	actorat[newobj->tilex][newobj->tiley] = 0;		// don't use original spot

	switch (dir)
	{
	case 0:
		newobj->tilex++;
		break;
	case 1:
		newobj->tiley--;
		break;
	case 2:
		newobj->tilex--;
		break;
	case 3:
		newobj->tiley++;
		break;
	}

	actorat[newobj->tilex][newobj->tiley] = act_enc(newobj);
}



/*
==================
=
= A_DeathScream
=
==================
*/

void A_DeathScream (objtype *ob)
{
#ifndef UPLOAD
#ifndef SPEAR
	if (gamestate.mapon==9 && !US_RndT())
#else
	if ((gamestate.mapon==18 || gamestate.mapon==19) && !US_RndT())
#endif
	{
	 switch(ob->obclass)
	 {
	  case mutantobj:
	  case guardobj:
	  case officerobj:
	  case ssobj:
	  case dogobj:
		PlaySoundLocActor(DEATHSCREAM6SND,ob);
		return;
	 }
	}
#endif

	switch (ob->obclass)
	{
	case mutantobj:
		PlaySoundLocActor(AHHHGSND,ob);
		break;

	case guardobj:
		{
		 s16 sounds[9]={ DEATHSCREAM1SND,
				 DEATHSCREAM2SND,
				 DEATHSCREAM3SND,
				 DEATHSCREAM4SND,
				 DEATHSCREAM5SND,
				 DEATHSCREAM7SND,
				 DEATHSCREAM8SND,
				 DEATHSCREAM9SND
				 };

		 #ifndef UPLOAD
		 PlaySoundLocActor(sounds[US_RndT()%8],ob);
		 #else
		 PlaySoundLocActor(sounds[US_RndT()%2],ob);
		 #endif
		}
		break;
	case officerobj:
		PlaySoundLocActor(NEINSOVASSND,ob);
		break;
	case ssobj:
		PlaySoundLocActor(LEBENSND,ob);	// JAB
		break;
	case dogobj:
		PlaySoundLocActor(DOGDEATHSND,ob);	// JAB
		break;
#ifndef SPEAR
	case bossobj:
		SD_PlaySound(MUTTISND);				// JAB
		break;
	case schabbobj:
		SD_PlaySound(MEINGOTTSND);
		break;
	case fakeobj:
		SD_PlaySound(HITLERHASND);
		break;
	case mechahitlerobj:
		SD_PlaySound(SCHEISTSND);
		break;
	case realhitlerobj:
		SD_PlaySound(EVASND);
		break;
	case gretelobj:
		SD_PlaySound(MEINSND);
		break;
	case giftobj:
		SD_PlaySound(DONNERSND);
		break;
	case fatobj:
		SD_PlaySound(ROSESND);
		break;
#else
	case spectreobj:
		SD_PlaySound(GHOSTFADESND);
		break;
	case angelobj:
		SD_PlaySound(ANGELDEATHSND);
		break;
	case transobj:
		SD_PlaySound(TRANSDEATHSND);
		break;
	case uberobj:
		SD_PlaySound(UBERDEATHSND);
		break;
	case willobj:
		SD_PlaySound(WILHELMDEATHSND);
		break;
	case deathobj:
		SD_PlaySound(KNIGHTDEATHSND);
		break;
#endif
	}
}


/*
=============================================================================

						 SPEAR ACTORS

=============================================================================
*/

#ifdef SPEAR

void T_Launch (objtype *ob);
void T_Will (objtype *ob);

//
// trans
//
const statetype s_transstand = {FALSE,SPR_TRANS_W1,0,T_Stand,NULL,&s_transstand};

const statetype s_transchase1 = {FALSE,SPR_TRANS_W1,10,T_Chase,NULL,&s_transchase1s};
const statetype s_transchase1s = {FALSE,SPR_TRANS_W1,3,NULL,NULL,&s_transchase2};
const statetype s_transchase2 = {FALSE,SPR_TRANS_W2,8,T_Chase,NULL,&s_transchase3};
const statetype s_transchase3 = {FALSE,SPR_TRANS_W3,10,T_Chase,NULL,&s_transchase3s};
const statetype s_transchase3s = {FALSE,SPR_TRANS_W3,3,NULL,NULL,&s_transchase4};
const statetype s_transchase4 = {FALSE,SPR_TRANS_W4,8,T_Chase,NULL,&s_transchase1};

const statetype s_transdie0 = {FALSE,SPR_TRANS_W1,1,NULL,A_DeathScream,&s_transdie01};
const statetype s_transdie01 = {FALSE,SPR_TRANS_W1,1,NULL,NULL,&s_transdie1};
const statetype s_transdie1 = {FALSE,SPR_TRANS_DIE1,15,NULL,NULL,&s_transdie2};
const statetype s_transdie2 = {FALSE,SPR_TRANS_DIE2,15,NULL,NULL,&s_transdie3};
const statetype s_transdie3 = {FALSE,SPR_TRANS_DIE3,15,NULL,NULL,&s_transdie4};
const statetype s_transdie4 = {FALSE,SPR_TRANS_DEAD,0,NULL,NULL,&s_transdie4};

const statetype s_transshoot1 = {FALSE,SPR_TRANS_SHOOT1,30,NULL,NULL,&s_transshoot2};
const statetype s_transshoot2 = {FALSE,SPR_TRANS_SHOOT2,10,NULL,T_Shoot,&s_transshoot3};
const statetype s_transshoot3 = {FALSE,SPR_TRANS_SHOOT3,10,NULL,T_Shoot,&s_transshoot4};
const statetype s_transshoot4 = {FALSE,SPR_TRANS_SHOOT2,10,NULL,T_Shoot,&s_transshoot5};
const statetype s_transshoot5 = {FALSE,SPR_TRANS_SHOOT3,10,NULL,T_Shoot,&s_transshoot6};
const statetype s_transshoot6 = {FALSE,SPR_TRANS_SHOOT2,10,NULL,T_Shoot,&s_transshoot7};
const statetype s_transshoot7 = {FALSE,SPR_TRANS_SHOOT3,10,NULL,T_Shoot,&s_transshoot8};
const statetype s_transshoot8 = {FALSE,SPR_TRANS_SHOOT1,10,NULL,NULL,&s_transchase1};


/*
===============
=
= SpawnTrans
=
===============
*/

void SpawnTrans (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (SoundBlasterPresent && DigiMode != sds_Off)
		s_transdie01.tictime = 105;

	SpawnNewObj (tilex,tiley,&s_transstand);
	newobj->obclass = transobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_trans];
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


//
// uber
//
void T_UShoot (objtype *ob);

const statetype s_uberstand = {FALSE,SPR_UBER_W1,0,T_Stand,NULL,&s_uberstand};

const statetype s_uberchase1 = {FALSE,SPR_UBER_W1,10,T_Chase,NULL,&s_uberchase1s};
const statetype s_uberchase1s = {FALSE,SPR_UBER_W1,3,NULL,NULL,&s_uberchase2};
const statetype s_uberchase2 = {FALSE,SPR_UBER_W2,8,T_Chase,NULL,&s_uberchase3};
const statetype s_uberchase3 = {FALSE,SPR_UBER_W3,10,T_Chase,NULL,&s_uberchase3s};
const statetype s_uberchase3s = {FALSE,SPR_UBER_W3,3,NULL,NULL,&s_uberchase4};
const statetype s_uberchase4 = {FALSE,SPR_UBER_W4,8,T_Chase,NULL,&s_uberchase1};

const statetype s_uberdie0 = {FALSE,SPR_UBER_W1,1,NULL,A_DeathScream,&s_uberdie01};
const statetype s_uberdie01 = {FALSE,SPR_UBER_W1,1,NULL,NULL,&s_uberdie1};
const statetype s_uberdie1 = {FALSE,SPR_UBER_DIE1,15,NULL,NULL,&s_uberdie2};
const statetype s_uberdie2 = {FALSE,SPR_UBER_DIE2,15,NULL,NULL,&s_uberdie3};
const statetype s_uberdie3 = {FALSE,SPR_UBER_DIE3,15,NULL,NULL,&s_uberdie4};
const statetype s_uberdie4 = {FALSE,SPR_UBER_DIE4,15,NULL,NULL,&s_uberdie5};
const statetype s_uberdie5 = {FALSE,SPR_UBER_DEAD,0,NULL,NULL,&s_uberdie5};

const statetype s_ubershoot1 = {FALSE,SPR_UBER_SHOOT1,30,NULL,NULL,&s_ubershoot2};
const statetype s_ubershoot2 = {FALSE,SPR_UBER_SHOOT2,12,NULL,T_UShoot,&s_ubershoot3};
const statetype s_ubershoot3 = {FALSE,SPR_UBER_SHOOT3,12,NULL,T_UShoot,&s_ubershoot4};
const statetype s_ubershoot4 = {FALSE,SPR_UBER_SHOOT4,12,NULL,T_UShoot,&s_ubershoot5};
const statetype s_ubershoot5 = {FALSE,SPR_UBER_SHOOT3,12,NULL,T_UShoot,&s_ubershoot6};
const statetype s_ubershoot6 = {FALSE,SPR_UBER_SHOOT2,12,NULL,T_UShoot,&s_ubershoot7};
const statetype s_ubershoot7 = {FALSE,SPR_UBER_SHOOT1,12,NULL,NULL,&s_uberchase1};


/*
===============
=
= SpawnUber
=
===============
*/

void SpawnUber (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (SoundBlasterPresent && DigiMode != sds_Off)
		s_uberdie01.tictime = 70;

	SpawnNewObj (tilex,tiley,&s_uberstand);
	newobj->obclass = uberobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_uber];
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
===============
=
= T_UShoot
=
===============
*/

void T_UShoot (objtype *ob)
{
	s16	dx,dy,dist;

	T_Shoot (ob);

	dx = abs(ob->tilex - player->tilex);
	dy = abs(ob->tiley - player->tiley);
	dist = dx>dy ? dx : dy;
	if (dist <= 1)
		TakeDamage (10,ob);
}


//
// will
//
const statetype s_willstand = {FALSE,SPR_WILL_W1,0,T_Stand,NULL,&s_willstand};

const statetype s_willchase1 = {FALSE,SPR_WILL_W1,10,T_Will,NULL,&s_willchase1s};
const statetype s_willchase1s = {FALSE,SPR_WILL_W1,3,NULL,NULL,&s_willchase2};
const statetype s_willchase2 = {FALSE,SPR_WILL_W2,8,T_Will,NULL,&s_willchase3};
const statetype s_willchase3 = {FALSE,SPR_WILL_W3,10,T_Will,NULL,&s_willchase3s};
const statetype s_willchase3s = {FALSE,SPR_WILL_W3,3,NULL,NULL,&s_willchase4};
const statetype s_willchase4 = {FALSE,SPR_WILL_W4,8,T_Will,NULL,&s_willchase1};

const statetype s_willdeathcam = {FALSE,SPR_WILL_W1,1,NULL,NULL,&s_willdie1};

const statetype s_willdie1 = {FALSE,SPR_WILL_W1,1,NULL,A_DeathScream,&s_willdie2};
const statetype s_willdie2 = {FALSE,SPR_WILL_W1,10,NULL,NULL,&s_willdie3};
const statetype s_willdie3 = {FALSE,SPR_WILL_DIE1,10,NULL,NULL,&s_willdie4};
const statetype s_willdie4 = {FALSE,SPR_WILL_DIE2,10,NULL,NULL,&s_willdie5};
const statetype s_willdie5 = {FALSE,SPR_WILL_DIE3,10,NULL,NULL,&s_willdie6};
const statetype s_willdie6 = {FALSE,SPR_WILL_DEAD,20,NULL,NULL,&s_willdie6};

const statetype s_willshoot1 = {FALSE,SPR_WILL_SHOOT1,30,NULL,NULL,&s_willshoot2};
const statetype s_willshoot2 = {FALSE,SPR_WILL_SHOOT2,10,NULL,T_Launch,&s_willshoot3};
const statetype s_willshoot3 = {FALSE,SPR_WILL_SHOOT3,10,NULL,T_Shoot,&s_willshoot4};
const statetype s_willshoot4 = {FALSE,SPR_WILL_SHOOT4,10,NULL,T_Shoot,&s_willshoot5};
const statetype s_willshoot5 = {FALSE,SPR_WILL_SHOOT3,10,NULL,T_Shoot,&s_willshoot6};
const statetype s_willshoot6 = {FALSE,SPR_WILL_SHOOT4,10,NULL,T_Shoot,&s_willchase1};


/*
===============
=
= SpawnWill
=
===============
*/

void SpawnWill (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (SoundBlasterPresent && DigiMode != sds_Off)
		s_willdie2.tictime = 70;

	SpawnNewObj (tilex,tiley,&s_willstand);
	newobj->obclass = willobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_will];
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
================
=
= T_Will
=
================
*/

void T_Will (objtype *ob)
{
	s32 move;
	s16	dx,dy,dist;
	boolean	dodge;

	dodge = FALSE;
	dx = abs(ob->tilex - player->tilex);
	dy = abs(ob->tiley - player->tiley);
	dist = dx>dy ? dx : dy;

	if (CheckLine(ob))						// got a shot at player?
	{
		if ( US_RndT() < (tics<<3) )
		{
		//
		// go into attack frame
		//
			if (ob->obclass == willobj)
				NewState (ob,&s_willshoot1);
			else if (ob->obclass == angelobj)
				NewState (ob,&s_angelshoot1);
			else
				NewState (ob,&s_deathshoot1);
			return;
		}
		dodge = TRUE;
	}

	if (ob->dir == nodir)
	{
		if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (ob->distance < 0)
		{
		//
		// waiting for a door to open
		//
			OpenDoor (-ob->distance-1);
			if (doorobjlist[-ob->distance-1].action != dr_open)
				return;
			ob->distance = TILEGLOBAL;	// go ahead, the door is now opoen
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		if (dist <4)
			SelectRunDir (ob);
		else if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}


//
// death
//
const statetype s_deathstand = {FALSE,SPR_DEATH_W1,0,T_Stand,NULL,&s_deathstand};

const statetype s_deathchase1 = {FALSE,SPR_DEATH_W1,10,T_Will,NULL,&s_deathchase1s};
const statetype s_deathchase1s = {FALSE,SPR_DEATH_W1,3,NULL,NULL,&s_deathchase2};
const statetype s_deathchase2 = {FALSE,SPR_DEATH_W2,8,T_Will,NULL,&s_deathchase3};
const statetype s_deathchase3 = {FALSE,SPR_DEATH_W3,10,T_Will,NULL,&s_deathchase3s};
const statetype s_deathchase3s = {FALSE,SPR_DEATH_W3,3,NULL,NULL,&s_deathchase4};
const statetype s_deathchase4 = {FALSE,SPR_DEATH_W4,8,T_Will,NULL,&s_deathchase1};

const statetype s_deathdeathcam = {FALSE,SPR_DEATH_W1,1,NULL,NULL,&s_deathdie1};

const statetype s_deathdie1 = {FALSE,SPR_DEATH_W1,1,NULL,A_DeathScream,&s_deathdie2};
const statetype s_deathdie2 = {FALSE,SPR_DEATH_W1,10,NULL,NULL,&s_deathdie3};
const statetype s_deathdie3 = {FALSE,SPR_DEATH_DIE1,10,NULL,NULL,&s_deathdie4};
const statetype s_deathdie4 = {FALSE,SPR_DEATH_DIE2,10,NULL,NULL,&s_deathdie5};
const statetype s_deathdie5 = {FALSE,SPR_DEATH_DIE3,10,NULL,NULL,&s_deathdie6};
const statetype s_deathdie6 = {FALSE,SPR_DEATH_DIE4,10,NULL,NULL,&s_deathdie7};
const statetype s_deathdie7 = {FALSE,SPR_DEATH_DIE5,10,NULL,NULL,&s_deathdie8};
const statetype s_deathdie8 = {FALSE,SPR_DEATH_DIE6,10,NULL,NULL,&s_deathdie9};
const statetype s_deathdie9 = {FALSE,SPR_DEATH_DEAD,0,NULL,NULL,&s_deathdie9};

const statetype s_deathshoot1 = {FALSE,SPR_DEATH_SHOOT1,30,NULL,NULL,&s_deathshoot2};
const statetype s_deathshoot2 = {FALSE,SPR_DEATH_SHOOT2,10,NULL,T_Launch,&s_deathshoot3};
const statetype s_deathshoot3 = {FALSE,SPR_DEATH_SHOOT4,10,NULL,T_Shoot,&s_deathshoot4};
const statetype s_deathshoot4 = {FALSE,SPR_DEATH_SHOOT3,10,NULL,T_Launch,&s_deathshoot5};
const statetype s_deathshoot5 = {FALSE,SPR_DEATH_SHOOT4,10,NULL,T_Shoot,&s_deathchase1};


/*
===============
=
= SpawnDeath
=
===============
*/

void SpawnDeath (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (SoundBlasterPresent && DigiMode != sds_Off)
		s_deathdie2.tictime = 105;

	SpawnNewObj (tilex,tiley,&s_deathstand);
	newobj->obclass = deathobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_death];
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}

/*
===============
=
= T_Launch
=
===============
*/

void T_Launch (objtype *ob)
{
	s32	deltax,deltay;
	s16		iangle;

	deltax = player->x - ob->x;
	deltay = ob->y - player->y;
	iangle = AimAngle (deltay,deltax);
	if (ob->obclass == deathobj)
	{
		T_Shoot (ob);
		if (ob->state == &s_deathshoot2)
		{
			iangle-=4;
			if (iangle<0)
				iangle+=ANGLES;
		}
		else
		{
			iangle+=4;
			if (iangle>=ANGLES)
				iangle-=ANGLES;
		}
	}

	GetNewActor ();
	newobj->state = &s_rocket;
	newobj->ticcount = 1;

	newobj->tilex = ob->tilex;
	newobj->tiley = ob->tiley;
	newobj->x = ob->x;
	newobj->y = ob->y;
	newobj->obclass = rocketobj;
	switch(ob->obclass)
	{
	case deathobj:
		newobj->state = &s_hrocket;
		newobj->obclass = hrocketobj;
		PlaySoundLocActor (KNIGHTMISSILESND,newobj);
		break;
	case angelobj:
		newobj->state = &s_spark1;
		newobj->obclass = sparkobj;
		PlaySoundLocActor (ANGELFIRESND,newobj);
		break;
	default:
		PlaySoundLocActor (MISSILEFIRESND,newobj);
	}

	newobj->dir = nodir;
	newobj->angle = iangle;
	newobj->speed = 0x2000l;
	newobj->flags = FL_NONMARK;
	newobj->active = TRUE;
}



//
// angel
//
void A_Relaunch (objtype *ob);
void A_Victory (objtype *ob);
void A_StartAttack (objtype *ob);
void A_Breathing (objtype *ob);

const statetype s_angelstand = {FALSE,SPR_ANGEL_W1,0,T_Stand,NULL,&s_angelstand};

const statetype s_angelchase1 = {FALSE,SPR_ANGEL_W1,10,T_Will,NULL,&s_angelchase1s};
const statetype s_angelchase1s = {FALSE,SPR_ANGEL_W1,3,NULL,NULL,&s_angelchase2};
const statetype s_angelchase2 = {FALSE,SPR_ANGEL_W2,8,T_Will,NULL,&s_angelchase3};
const statetype s_angelchase3 = {FALSE,SPR_ANGEL_W3,10,T_Will,NULL,&s_angelchase3s};
const statetype s_angelchase3s = {FALSE,SPR_ANGEL_W3,3,NULL,NULL,&s_angelchase4};
const statetype s_angelchase4 = {FALSE,SPR_ANGEL_W4,8,T_Will,NULL,&s_angelchase1};

const statetype s_angeldie1 = {FALSE,SPR_ANGEL_W1,1,NULL,A_DeathScream,&s_angeldie11};
const statetype s_angeldie11 = {FALSE,SPR_ANGEL_W1,1,NULL,NULL,&s_angeldie2};
const statetype s_angeldie2 = {FALSE,SPR_ANGEL_DIE1,10,NULL,A_Slurpie,&s_angeldie3};
const statetype s_angeldie3 = {FALSE,SPR_ANGEL_DIE2,10,NULL,NULL,&s_angeldie4};
const statetype s_angeldie4 = {FALSE,SPR_ANGEL_DIE3,10,NULL,NULL,&s_angeldie5};
const statetype s_angeldie5 = {FALSE,SPR_ANGEL_DIE4,10,NULL,NULL,&s_angeldie6};
const statetype s_angeldie6 = {FALSE,SPR_ANGEL_DIE5,10,NULL,NULL,&s_angeldie7};
const statetype s_angeldie7 = {FALSE,SPR_ANGEL_DIE6,10,NULL,NULL,&s_angeldie8};
const statetype s_angeldie8 = {FALSE,SPR_ANGEL_DIE7,10,NULL,NULL,&s_angeldie9};
const statetype s_angeldie9 = {FALSE,SPR_ANGEL_DEAD,130,NULL,A_Victory,&s_angeldie9};

const statetype s_angelshoot1 = {FALSE,SPR_ANGEL_SHOOT1,10,NULL,A_StartAttack,&s_angelshoot2};
const statetype s_angelshoot2 = {FALSE,SPR_ANGEL_SHOOT2,20,NULL,T_Launch,&s_angelshoot3};
const statetype s_angelshoot3 = {FALSE,SPR_ANGEL_SHOOT1,10,NULL,A_Relaunch,&s_angelshoot2};

const statetype s_angeltired = {FALSE,SPR_ANGEL_TIRED1,40,NULL,A_Breathing,&s_angeltired2};
const statetype s_angeltired2 = {FALSE,SPR_ANGEL_TIRED2,40,NULL,NULL,&s_angeltired3};
const statetype s_angeltired3 = {FALSE,SPR_ANGEL_TIRED1,40,NULL,A_Breathing,&s_angeltired4};
const statetype s_angeltired4 = {FALSE,SPR_ANGEL_TIRED2,40,NULL,NULL,&s_angeltired5};
const statetype s_angeltired5 = {FALSE,SPR_ANGEL_TIRED1,40,NULL,A_Breathing,&s_angeltired6};
const statetype s_angeltired6 = {FALSE,SPR_ANGEL_TIRED2,40,NULL,NULL,&s_angeltired7};
const statetype s_angeltired7 = {FALSE,SPR_ANGEL_TIRED1,40,NULL,A_Breathing,&s_angelchase1};

const statetype s_spark1 = {FALSE,SPR_SPARK1,6,T_Projectile,NULL,&s_spark2};
const statetype s_spark2 = {FALSE,SPR_SPARK2,6,T_Projectile,NULL,&s_spark3};
const statetype s_spark3 = {FALSE,SPR_SPARK3,6,T_Projectile,NULL,&s_spark4};
const statetype s_spark4 = {FALSE,SPR_SPARK4,6,T_Projectile,NULL,&s_spark1};



void A_Slurpie (objtype *ob)
{
 SD_PlaySound(SLURPIESND);
}


void A_Breathing (objtype *ob)
{
 SD_PlaySound(ANGELTIREDSND);
}

/*
===============
=
= SpawnAngel
=
===============
*/

void SpawnAngel (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;


	if (SoundBlasterPresent && DigiMode != sds_Off)
		s_angeldie11.tictime = 105;

	SpawnNewObj (tilex,tiley,&s_angelstand);
	newobj->obclass = angelobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_angel];
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
=================
=
= A_Victory
=
=================
*/


void A_Victory (objtype *ob)
{
	playstate = ex_victorious;
}


/*
=================
=
= A_StartAttack
=
=================
*/

void A_StartAttack (objtype *ob)
{
	ob->temp1 = 0;
}


/*
=================
=
= A_Relaunch
=
=================
*/

void A_Relaunch (objtype *ob)
{
	if (++ob->temp1 == 3)
	{
		NewState (ob,&s_angeltired);
		return;
	}

	if (US_RndT()&1)
	{
		NewState (ob,&s_angelchase1);
		return;
	}
}




//
// spectre
//
void T_SpectreWait (objtype *ob);
void A_Dormant (objtype *ob);

const statetype s_spectrewait1 = {FALSE,SPR_SPECTRE_W1,10,T_Stand,NULL,&s_spectrewait2};
const statetype s_spectrewait2 = {FALSE,SPR_SPECTRE_W2,10,T_Stand,NULL,&s_spectrewait3};
const statetype s_spectrewait3 = {FALSE,SPR_SPECTRE_W3,10,T_Stand,NULL,&s_spectrewait4};
const statetype s_spectrewait4 = {FALSE,SPR_SPECTRE_W4,10,T_Stand,NULL,&s_spectrewait1};

const statetype s_spectrechase1 = {FALSE,SPR_SPECTRE_W1,10,T_Ghosts,NULL,&s_spectrechase2};
const statetype s_spectrechase2 = {FALSE,SPR_SPECTRE_W2,10,T_Ghosts,NULL,&s_spectrechase3};
const statetype s_spectrechase3 = {FALSE,SPR_SPECTRE_W3,10,T_Ghosts,NULL,&s_spectrechase4};
const statetype s_spectrechase4 = {FALSE,SPR_SPECTRE_W4,10,T_Ghosts,NULL,&s_spectrechase1};

const statetype s_spectredie1 = {FALSE,SPR_SPECTRE_F1,10,NULL,NULL,&s_spectredie2};
const statetype s_spectredie2 = {FALSE,SPR_SPECTRE_F2,10,NULL,NULL,&s_spectredie3};
const statetype s_spectredie3 = {FALSE,SPR_SPECTRE_F3,10,NULL,NULL,&s_spectredie4};
const statetype s_spectredie4 = {FALSE,SPR_SPECTRE_F4,300,NULL,NULL,&s_spectrewake};
const statetype s_spectrewake = {FALSE,SPR_SPECTRE_F4,10,NULL,A_Dormant,&s_spectrewake};

/*
===============
=
= SpawnSpectre
=
===============
*/

void SpawnSpectre (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	SpawnNewObj (tilex,tiley,&s_spectrewait1);
	newobj->obclass = spectreobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_spectre];
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH; // |FL_NEVERMARK|FL_NONMARK;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
===============
=
= A_Dormant
=
===============
*/

void A_Dormant (objtype *ob)
{
	s32	deltax,deltay;
	s16	xl,xh,yl,yh;
	s16	x,y;
	u16	tile;

	deltax = ob->x - player->x;
	if (deltax < -MINACTORDIST || deltax > MINACTORDIST)
		goto moveok;
	deltay = ob->y - player->y;
	if (deltay < -MINACTORDIST || deltay > MINACTORDIST)
		goto moveok;

	return;
moveok:

	xl = (ob->x-MINDIST) >> TILESHIFT;
	xh = (ob->x+MINDIST) >> TILESHIFT;
	yl = (ob->y-MINDIST) >> TILESHIFT;
	yh = (ob->y+MINDIST) >> TILESHIFT;

	for (y=yl ; y<=yh ; y++)
		for (x=xl ; x<=xh ; x++)
		{
			tile = actorat[x][y];
			if (!tile)
				continue;
			if (tile<256)
				return;
			if (((objtype *)tile)->flags&FL_SHOOTABLE)
				return;
		}

	ob->flags |= FL_AMBUSH | FL_SHOOTABLE;
	ob->flags &= ~FL_ATTACKMODE;
	ob->dir = nodir;
	NewState (ob,&s_spectrewait1);
}


#endif

/*
=============================================================================

						 SCHABBS / GIFT / FAT

=============================================================================
*/

#ifndef SPEAR
/*
===============
=
= SpawnGhosts
=
===============
*/

void SpawnGhosts (s16 which, s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	switch(which)
	{
	 case en_blinky:
	   SpawnNewObj (tilex,tiley,&s_blinkychase1);
	   break;
	 case en_clyde:
	   SpawnNewObj (tilex,tiley,&s_clydechase1);
	   break;
	 case en_pinky:
	   SpawnNewObj (tilex,tiley,&s_pinkychase1);
	   break;
	 case en_inky:
	   SpawnNewObj (tilex,tiley,&s_inkychase1);
	   break;
	}

	newobj->obclass = ghostobj;
	newobj->speed = SPDDOG;

	newobj->dir = east;
	newobj->flags |= FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}



void	T_Gift (objtype *ob);
void	T_GiftThrow (objtype *ob);

void	T_Fat (objtype *ob);
void	T_FatThrow (objtype *ob);

//
// schabb
//
const statetype s_schabbstand = {FALSE,SPR_SCHABB_W1,0,T_Stand,NULL,&s_schabbstand};

const statetype s_schabbchase1 = {FALSE,SPR_SCHABB_W1,10,T_Schabb,NULL,&s_schabbchase1s};
const statetype s_schabbchase1s = {FALSE,SPR_SCHABB_W1,3,NULL,NULL,&s_schabbchase2};
const statetype s_schabbchase2 = {FALSE,SPR_SCHABB_W2,8,T_Schabb,NULL,&s_schabbchase3};
const statetype s_schabbchase3 = {FALSE,SPR_SCHABB_W3,10,T_Schabb,NULL,&s_schabbchase3s};
const statetype s_schabbchase3s = {FALSE,SPR_SCHABB_W3,3,NULL,NULL,&s_schabbchase4};
const statetype s_schabbchase4 = {FALSE,SPR_SCHABB_W4,8,T_Schabb,NULL,&s_schabbchase1};

const statetype s_schabbdeathcam = {FALSE,SPR_SCHABB_W1,1,NULL,NULL,&s_schabbdie1};

const statetype s_schabbdie1 = {FALSE,SPR_SCHABB_W1,10,NULL,A_DeathScream,&s_schabbdie2};
statetype s_schabbdie2 = {FALSE,SPR_SCHABB_W1,10,NULL,NULL,&s_schabbdie3};
const statetype s_schabbdie3 = {FALSE,SPR_SCHABB_DIE1,10,NULL,NULL,&s_schabbdie4};
const statetype s_schabbdie4 = {FALSE,SPR_SCHABB_DIE2,10,NULL,NULL,&s_schabbdie5};
const statetype s_schabbdie5 = {FALSE,SPR_SCHABB_DIE3,10,NULL,NULL,&s_schabbdie6};
const statetype s_schabbdie6 = {FALSE,SPR_SCHABB_DEAD,20,NULL,A_StartDeathCam,&s_schabbdie6};

const statetype s_schabbshoot1 = {FALSE,SPR_SCHABB_SHOOT1,30,NULL,NULL,&s_schabbshoot2};
const statetype s_schabbshoot2 = {FALSE,SPR_SCHABB_SHOOT2,10,NULL,T_SchabbThrow,&s_schabbchase1};

const statetype s_needle1 = {FALSE,SPR_HYPO1,6,T_Projectile,NULL,&s_needle2};
const statetype s_needle2 = {FALSE,SPR_HYPO2,6,T_Projectile,NULL,&s_needle3};
const statetype s_needle3 = {FALSE,SPR_HYPO3,6,T_Projectile,NULL,&s_needle4};
const statetype s_needle4 = {FALSE,SPR_HYPO4,6,T_Projectile,NULL,&s_needle1};


//
// gift
//
const statetype s_giftstand = {FALSE,SPR_GIFT_W1,0,T_Stand,NULL,&s_giftstand};

const statetype s_giftchase1 = {FALSE,SPR_GIFT_W1,10,T_Gift,NULL,&s_giftchase1s};
const statetype s_giftchase1s = {FALSE,SPR_GIFT_W1,3,NULL,NULL,&s_giftchase2};
const statetype s_giftchase2 = {FALSE,SPR_GIFT_W2,8,T_Gift,NULL,&s_giftchase3};
const statetype s_giftchase3 = {FALSE,SPR_GIFT_W3,10,T_Gift,NULL,&s_giftchase3s};
const statetype s_giftchase3s = {FALSE,SPR_GIFT_W3,3,NULL,NULL,&s_giftchase4};
const statetype s_giftchase4 = {FALSE,SPR_GIFT_W4,8,T_Gift,NULL,&s_giftchase1};

const statetype s_giftdeathcam = {FALSE,SPR_GIFT_W1,1,NULL,NULL,&s_giftdie1};

const statetype s_giftdie1 = {FALSE,SPR_GIFT_W1,1,NULL,A_DeathScream,&s_giftdie2};
statetype s_giftdie2 = {FALSE,SPR_GIFT_W1,10,NULL,NULL,&s_giftdie3};
const statetype s_giftdie3 = {FALSE,SPR_GIFT_DIE1,10,NULL,NULL,&s_giftdie4};
const statetype s_giftdie4 = {FALSE,SPR_GIFT_DIE2,10,NULL,NULL,&s_giftdie5};
const statetype s_giftdie5 = {FALSE,SPR_GIFT_DIE3,10,NULL,NULL,&s_giftdie6};
const statetype s_giftdie6 = {FALSE,SPR_GIFT_DEAD,20,NULL,A_StartDeathCam,&s_giftdie6};

const statetype s_giftshoot1 = {FALSE,SPR_GIFT_SHOOT1,30,NULL,NULL,&s_giftshoot2};
const statetype s_giftshoot2 = {FALSE,SPR_GIFT_SHOOT2,10,NULL,T_GiftThrow,&s_giftchase1};


//
// fat
//
const statetype s_fatstand = {FALSE,SPR_FAT_W1,0,T_Stand,NULL,&s_fatstand};

const statetype s_fatchase1 = {FALSE,SPR_FAT_W1,10,T_Fat,NULL,&s_fatchase1s};
const statetype s_fatchase1s = {FALSE,SPR_FAT_W1,3,NULL,NULL,&s_fatchase2};
const statetype s_fatchase2 = {FALSE,SPR_FAT_W2,8,T_Fat,NULL,&s_fatchase3};
const statetype s_fatchase3 = {FALSE,SPR_FAT_W3,10,T_Fat,NULL,&s_fatchase3s};
const statetype s_fatchase3s = {FALSE,SPR_FAT_W3,3,NULL,NULL,&s_fatchase4};
const statetype s_fatchase4 = {FALSE,SPR_FAT_W4,8,T_Fat,NULL,&s_fatchase1};

const statetype s_fatdeathcam = {FALSE,SPR_FAT_W1,1,NULL,NULL,&s_fatdie1};

const statetype s_fatdie1 = {FALSE,SPR_FAT_W1,1,NULL,A_DeathScream,&s_fatdie2};
statetype s_fatdie2 = {FALSE,SPR_FAT_W1,10,NULL,NULL,&s_fatdie3};
const statetype s_fatdie3 = {FALSE,SPR_FAT_DIE1,10,NULL,NULL,&s_fatdie4};
const statetype s_fatdie4 = {FALSE,SPR_FAT_DIE2,10,NULL,NULL,&s_fatdie5};
const statetype s_fatdie5 = {FALSE,SPR_FAT_DIE3,10,NULL,NULL,&s_fatdie6};
const statetype s_fatdie6 = {FALSE,SPR_FAT_DEAD,20,NULL,A_StartDeathCam,&s_fatdie6};

const statetype s_fatshoot1 = {FALSE,SPR_FAT_SHOOT1,30,NULL,NULL,&s_fatshoot2};
const statetype s_fatshoot2 = {FALSE,SPR_FAT_SHOOT2,10,NULL,T_GiftThrow,&s_fatshoot3};
const statetype s_fatshoot3 = {FALSE,SPR_FAT_SHOOT3,10,NULL,T_Shoot,&s_fatshoot4};
const statetype s_fatshoot4 = {FALSE,SPR_FAT_SHOOT4,10,NULL,T_Shoot,&s_fatshoot5};
const statetype s_fatshoot5 = {FALSE,SPR_FAT_SHOOT3,10,NULL,T_Shoot,&s_fatshoot6};
const statetype s_fatshoot6 = {FALSE,SPR_FAT_SHOOT4,10,NULL,T_Shoot,&s_fatchase1};


/*
===============
=
= SpawnSchabbs
=
===============
*/

void SpawnSchabbs (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (DigiMode != sds_Off)
		s_schabbdie2.tictime = 140;
	else
		s_schabbdie2.tictime = 5;

	SpawnNewObj (tilex,tiley,&s_schabbstand);
	newobj->speed = SPDPATROL;

	newobj->obclass = schabbobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_schabbs];
	newobj->dir = south;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
===============
=
= SpawnGift
=
===============
*/

void SpawnGift (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (DigiMode != sds_Off)
	  s_giftdie2.tictime = 140;
	else
	  s_giftdie2.tictime = 5;

	SpawnNewObj (tilex,tiley,&s_giftstand);
	newobj->speed = SPDPATROL;

	newobj->obclass = giftobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_gift];
	newobj->dir = north;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
===============
=
= SpawnFat
=
===============
*/

void SpawnFat (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (DigiMode != sds_Off)
	  s_fatdie2.tictime = 140;
	else
	  s_fatdie2.tictime = 5;

	SpawnNewObj (tilex,tiley,&s_fatstand);
	newobj->speed = SPDPATROL;

	newobj->obclass = fatobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_fat];
	newobj->dir = south;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
=================
=
= T_SchabbThrow
=
=================
*/

void T_SchabbThrow (objtype *ob)
{
	s32	deltax,deltay;
	s16		iangle;

	deltax = player->x - ob->x;
	deltay = ob->y - player->y;
	iangle = AimAngle (deltay,deltax);

	GetNewActor ();
	newobj->state = &s_needle1;
	newobj->ticcount = 1;

	newobj->tilex = ob->tilex;
	newobj->tiley = ob->tiley;
	newobj->x = ob->x;
	newobj->y = ob->y;
	newobj->obclass = needleobj;
	newobj->dir = nodir;
	newobj->angle = iangle;
	newobj->speed = 0x2000l;

	newobj->flags = FL_NONMARK;
	newobj->active = TRUE;

	PlaySoundLocActor (SCHABBSTHROWSND,newobj);
}

/*
=================
=
= T_GiftThrow
=
=================
*/

void T_GiftThrow (objtype *ob)
{
	s32	deltax,deltay;
	s16		iangle;

	deltax = player->x - ob->x;
	deltay = ob->y - player->y;
	iangle = AimAngle (deltay,deltax);

	GetNewActor ();
	newobj->state = &s_rocket;
	newobj->ticcount = 1;

	newobj->tilex = ob->tilex;
	newobj->tiley = ob->tiley;
	newobj->x = ob->x;
	newobj->y = ob->y;
	newobj->obclass = rocketobj;
	newobj->dir = nodir;
	newobj->angle = iangle;
	newobj->speed = 0x2000l;
	newobj->flags = FL_NONMARK;
	newobj->active = TRUE;

	PlaySoundLocActor (MISSILEFIRESND,newobj);
}



/*
=================
=
= T_Schabb
=
=================
*/

void T_Schabb (objtype *ob)
{
	s32 move;
	s16	dx,dy,dist;
	boolean	dodge;

	dodge = FALSE;
	dx = abs(ob->tilex - player->tilex);
	dy = abs(ob->tiley - player->tiley);
	dist = dx>dy ? dx : dy;

	if (CheckLine(ob))						// got a shot at player?
	{

		if ( US_RndT() < (tics<<3) )
		{
		//
		// go into attack frame
		//
			NewState (ob,&s_schabbshoot1);
			return;
		}
		dodge = TRUE;
	}

	if (ob->dir == nodir)
	{
		if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (ob->distance < 0)
		{
		//
		// waiting for a door to open
		//
			OpenDoor (-ob->distance-1);
			if (doorobjlist[-ob->distance-1].action != dr_open)
				return;
			ob->distance = TILEGLOBAL;	// go ahead, the door is now opoen
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		if (dist <4)
			SelectRunDir (ob);
		else if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}




/*
=================
=
= T_Gift
=
=================
*/

void T_Gift (objtype *ob)
{
	s32 move;
	s16	dx,dy,dist;
	boolean	dodge;

	dodge = FALSE;
	dx = abs(ob->tilex - player->tilex);
	dy = abs(ob->tiley - player->tiley);
	dist = dx>dy ? dx : dy;

	if (CheckLine(ob))						// got a shot at player?
	{

		if ( US_RndT() < (tics<<3) )
		{
		//
		// go into attack frame
		//
			NewState (ob,&s_giftshoot1);
			return;
		}
		dodge = TRUE;
	}

	if (ob->dir == nodir)
	{
		if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (ob->distance < 0)
		{
		//
		// waiting for a door to open
		//
			OpenDoor (-ob->distance-1);
			if (doorobjlist[-ob->distance-1].action != dr_open)
				return;
			ob->distance = TILEGLOBAL;	// go ahead, the door is now opoen
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		if (dist <4)
			SelectRunDir (ob);
		else if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}




/*
=================
=
= T_Fat
=
=================
*/

void T_Fat (objtype *ob)
{
	s32 move;
	s16	dx,dy,dist;
	boolean	dodge;

	dodge = FALSE;
	dx = abs(ob->tilex - player->tilex);
	dy = abs(ob->tiley - player->tiley);
	dist = dx>dy ? dx : dy;

	if (CheckLine(ob))						// got a shot at player?
	{

		if ( US_RndT() < (tics<<3) )
		{
		//
		// go into attack frame
		//
			NewState (ob,&s_fatshoot1);
			return;
		}
		dodge = TRUE;
	}

	if (ob->dir == nodir)
	{
		if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (ob->distance < 0)
		{
		//
		// waiting for a door to open
		//
			OpenDoor (-ob->distance-1);
			if (doorobjlist[-ob->distance-1].action != dr_open)
				return;
			ob->distance = TILEGLOBAL;	// go ahead, the door is now opoen
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		if (dist <4)
			SelectRunDir (ob);
		else if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}



/*
=============================================================================

							HITLERS

=============================================================================
*/


//
// fake
//
const statetype s_fakestand = {FALSE,SPR_FAKE_W1,0,T_Stand,NULL,&s_fakestand};

const statetype s_fakechase1 = {FALSE,SPR_FAKE_W1,10,T_Fake,NULL,&s_fakechase1s};
const statetype s_fakechase1s = {FALSE,SPR_FAKE_W1,3,NULL,NULL,&s_fakechase2};
const statetype s_fakechase2 = {FALSE,SPR_FAKE_W2,8,T_Fake,NULL,&s_fakechase3};
const statetype s_fakechase3 = {FALSE,SPR_FAKE_W3,10,T_Fake,NULL,&s_fakechase3s};
const statetype s_fakechase3s = {FALSE,SPR_FAKE_W3,3,NULL,NULL,&s_fakechase4};
const statetype s_fakechase4 = {FALSE,SPR_FAKE_W4,8,T_Fake,NULL,&s_fakechase1};

const statetype s_fakedie1 = {FALSE,SPR_FAKE_DIE1,10,NULL,A_DeathScream,&s_fakedie2};
const statetype s_fakedie2 = {FALSE,SPR_FAKE_DIE2,10,NULL,NULL,&s_fakedie3};
const statetype s_fakedie3 = {FALSE,SPR_FAKE_DIE3,10,NULL,NULL,&s_fakedie4};
const statetype s_fakedie4 = {FALSE,SPR_FAKE_DIE4,10,NULL,NULL,&s_fakedie5};
const statetype s_fakedie5 = {FALSE,SPR_FAKE_DIE5,10,NULL,NULL,&s_fakedie6};
const statetype s_fakedie6 = {FALSE,SPR_FAKE_DEAD,0,NULL,NULL,&s_fakedie6};

const statetype s_fakeshoot1 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot2};
const statetype s_fakeshoot2 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot3};
const statetype s_fakeshoot3 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot4};
const statetype s_fakeshoot4 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot5};
const statetype s_fakeshoot5 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot6};
const statetype s_fakeshoot6 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot7};
const statetype s_fakeshoot7 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot8};
const statetype s_fakeshoot8 = {FALSE,SPR_FAKE_SHOOT,8,NULL,T_FakeFire,&s_fakeshoot9};
const statetype s_fakeshoot9 = {FALSE,SPR_FAKE_SHOOT,8,NULL,NULL,&s_fakechase1};

const statetype s_fire1 = {FALSE,SPR_FIRE1,6,NULL,T_Projectile,&s_fire2};
const statetype s_fire2 = {FALSE,SPR_FIRE2,6,NULL,T_Projectile,&s_fire1};

//
// hitler
//
const statetype s_mechastand = {FALSE,SPR_MECHA_W1,0,T_Stand,NULL,&s_mechastand};

const statetype s_mechachase1 = {FALSE,SPR_MECHA_W1,10,T_Chase,A_MechaSound,&s_mechachase1s};
const statetype s_mechachase1s = {FALSE,SPR_MECHA_W1,6,NULL,NULL,&s_mechachase2};
const statetype s_mechachase2 = {FALSE,SPR_MECHA_W2,8,T_Chase,NULL,&s_mechachase3};
const statetype s_mechachase3 = {FALSE,SPR_MECHA_W3,10,T_Chase,A_MechaSound,&s_mechachase3s};
const statetype s_mechachase3s = {FALSE,SPR_MECHA_W3,6,NULL,NULL,&s_mechachase4};
const statetype s_mechachase4 = {FALSE,SPR_MECHA_W4,8,T_Chase,NULL,&s_mechachase1};

const statetype s_mechadie1 = {FALSE,SPR_MECHA_DIE1,10,NULL,A_DeathScream,&s_mechadie2};
const statetype s_mechadie2 = {FALSE,SPR_MECHA_DIE2,10,NULL,NULL,&s_mechadie3};
const statetype s_mechadie3 = {FALSE,SPR_MECHA_DIE3,10,NULL,A_HitlerMorph,&s_mechadie4};
const statetype s_mechadie4 = {FALSE,SPR_MECHA_DEAD,0,NULL,NULL,&s_mechadie4};

const statetype s_mechashoot1 = {FALSE,SPR_MECHA_SHOOT1,30,NULL,NULL,&s_mechashoot2};
const statetype s_mechashoot2 = {FALSE,SPR_MECHA_SHOOT2,10,NULL,T_Shoot,&s_mechashoot3};
const statetype s_mechashoot3 = {FALSE,SPR_MECHA_SHOOT3,10,NULL,T_Shoot,&s_mechashoot4};
const statetype s_mechashoot4 = {FALSE,SPR_MECHA_SHOOT2,10,NULL,T_Shoot,&s_mechashoot5};
const statetype s_mechashoot5 = {FALSE,SPR_MECHA_SHOOT3,10,NULL,T_Shoot,&s_mechashoot6};
const statetype s_mechashoot6 = {FALSE,SPR_MECHA_SHOOT2,10,NULL,T_Shoot,&s_mechachase1};


const statetype s_hitlerchase1 = {FALSE,SPR_HITLER_W1,6,T_Chase,NULL,&s_hitlerchase1s};
const statetype s_hitlerchase1s = {FALSE,SPR_HITLER_W1,4,NULL,NULL,&s_hitlerchase2};
const statetype s_hitlerchase2 = {FALSE,SPR_HITLER_W2,2,T_Chase,NULL,&s_hitlerchase3};
const statetype s_hitlerchase3 = {FALSE,SPR_HITLER_W3,6,T_Chase,NULL,&s_hitlerchase3s};
const statetype s_hitlerchase3s = {FALSE,SPR_HITLER_W3,4,NULL,NULL,&s_hitlerchase4};
const statetype s_hitlerchase4 = {FALSE,SPR_HITLER_W4,2,T_Chase,NULL,&s_hitlerchase1};

const statetype s_hitlerdeathcam = {FALSE,SPR_HITLER_W1,10,NULL,NULL,&s_hitlerdie1};

const statetype s_hitlerdie1 = {FALSE,SPR_HITLER_W1,1,NULL,A_DeathScream,&s_hitlerdie2};
statetype s_hitlerdie2 = {FALSE,SPR_HITLER_W1,10,NULL,NULL,&s_hitlerdie3};
const statetype s_hitlerdie3 = {FALSE,SPR_HITLER_DIE1,10,NULL,A_Slurpie,&s_hitlerdie4};
const statetype s_hitlerdie4 = {FALSE,SPR_HITLER_DIE2,10,NULL,NULL,&s_hitlerdie5};
const statetype s_hitlerdie5 = {FALSE,SPR_HITLER_DIE3,10,NULL,NULL,&s_hitlerdie6};
const statetype s_hitlerdie6 = {FALSE,SPR_HITLER_DIE4,10,NULL,NULL,&s_hitlerdie7};
const statetype s_hitlerdie7 = {FALSE,SPR_HITLER_DIE5,10,NULL,NULL,&s_hitlerdie8};
const statetype s_hitlerdie8 = {FALSE,SPR_HITLER_DIE6,10,NULL,NULL,&s_hitlerdie9};
const statetype s_hitlerdie9 = {FALSE,SPR_HITLER_DIE7,10,NULL,NULL,&s_hitlerdie10};
const statetype s_hitlerdie10 = {FALSE,SPR_HITLER_DEAD,20,NULL,A_StartDeathCam,&s_hitlerdie10};

const statetype s_hitlershoot1 = {FALSE,SPR_HITLER_SHOOT1,30,NULL,NULL,&s_hitlershoot2};
const statetype s_hitlershoot2 = {FALSE,SPR_HITLER_SHOOT2,10,NULL,T_Shoot,&s_hitlershoot3};
const statetype s_hitlershoot3 = {FALSE,SPR_HITLER_SHOOT3,10,NULL,T_Shoot,&s_hitlershoot4};
const statetype s_hitlershoot4 = {FALSE,SPR_HITLER_SHOOT2,10,NULL,T_Shoot,&s_hitlershoot5};
const statetype s_hitlershoot5 = {FALSE,SPR_HITLER_SHOOT3,10,NULL,T_Shoot,&s_hitlershoot6};
const statetype s_hitlershoot6 = {FALSE,SPR_HITLER_SHOOT2,10,NULL,T_Shoot,&s_hitlerchase1};



/*
===============
=
= SpawnFakeHitler
=
===============
*/

void SpawnFakeHitler (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;


	if (DigiMode != sds_Off)
	  s_hitlerdie2.tictime = 140;
	else
	  s_hitlerdie2.tictime = 5;

	SpawnNewObj (tilex,tiley,&s_fakestand);
	newobj->speed = SPDPATROL;

	newobj->obclass = fakeobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_fake];
	newobj->dir = north;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
===============
=
= SpawnHitler
=
===============
*/

void SpawnHitler (s16 tilex, s16 tiley)
{
	u8 *map;
	u16 tile;

	if (DigiMode != sds_Off)
		s_hitlerdie2.tictime = 140;
	else
		s_hitlerdie2.tictime = 5;


	SpawnNewObj (tilex,tiley,&s_mechastand);
	newobj->speed = SPDPATROL;

	newobj->obclass = mechahitlerobj;
	newobj->hitpoints = starthitpoints[gamestate.difficulty][en_hitler];
	newobj->dir = south;
	newobj->flags |= FL_SHOOTABLE|FL_AMBUSH;
	if (!loadedgame)
	  gamestate.killtotal++;
}


/*
===============
=
= A_HitlerMorph
=
===============
*/

void A_HitlerMorph (objtype *ob)
{
	u16	*map,tile,hitpoints[4]={500,700,800,900};


	SpawnNewObj (ob->tilex,ob->tiley,&s_hitlerchase1);
	newobj->speed = SPDPATROL*5;

	newobj->x = ob->x;
	newobj->y = ob->y;

	newobj->distance = ob->distance;
	newobj->dir = ob->dir;
	newobj->flags = ob->flags | FL_SHOOTABLE;

	newobj->obclass = realhitlerobj;
	newobj->hitpoints = hitpoints[gamestate.difficulty];
}


////////////////////////////////////////////////////////
//
// A_MechaSound
// A_Slurpie
//
////////////////////////////////////////////////////////
void A_MechaSound (objtype *ob)
{
	if (areabyplayer[ob->areanumber])
		PlaySoundLocActor (MECHSTEPSND,ob);
}



void A_Slurpie (objtype *ob)
{
 SD_PlaySound(SLURPIESND);
}

/*
=================
=
= T_FakeFire
=
=================
*/

void T_FakeFire (objtype *ob)
{
	s32	deltax,deltay;
	s16		iangle;

	deltax = player->x - ob->x;
	deltay = ob->y - player->y;
	iangle = AimAngle (deltay,deltax);

	GetNewActor ();
	newobj->state = &s_fire1;
	newobj->ticcount = 1;

	newobj->tilex = ob->tilex;
	newobj->tiley = ob->tiley;
	newobj->x = ob->x;
	newobj->y = ob->y;
	newobj->dir = nodir;
	newobj->angle = iangle;
	newobj->obclass = fireobj;
	newobj->speed = 0x1200l;
	newobj->flags = FL_NEVERMARK;
	newobj->active = TRUE;

	PlaySoundLocActor (FLAMETHROWERSND,newobj);
}



/*
=================
=
= T_Fake
=
=================
*/

void T_Fake (objtype *ob)
{
	s32 move;
	s16	dx,dy,dist;
	boolean	dodge;

	if (CheckLine(ob))			// got a shot at player?
	{
		if ( US_RndT() < (tics<<1) )
		{
		//
		// go into attack frame
		//
			NewState (ob,&s_fakeshoot1);
			return;
		}
	}

	if (ob->dir == nodir)
	{
		SelectDodgeDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		SelectDodgeDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}

#endif
/*
============================================================================

							STAND

============================================================================
*/


/*
===============
=
= T_Stand
=
===============
*/

void T_Stand (objtype *ob)
{
	SightPlayer (ob);
}


/*
============================================================================

								CHASE

============================================================================
*/

/*
=================
=
= T_Chase
=
=================
*/

void T_Chase (objtype *ob)
{
	s32 move;
	s16	dx,dy,dist,chance;
	boolean	dodge;

	if (gamestate.victoryflag)
		return;

	dodge = FALSE;
	if (CheckLine(ob))	// got a shot at player?
	{
		dx = abs(ob->tilex - player->tilex);
		dy = abs(ob->tiley - player->tiley);
		dist = dx>dy ? dx : dy;
		if (!dist || (dist==1 && ob->distance<0x4000) )
			chance = 300;
		else
			chance = (tics<<4)/dist;

		if ( US_RndT()<chance)
		{
		//
		// go into attack frame
		//
			switch (ob->obclass)
			{
			case guardobj:
				NewState (ob,&s_grdshoot1);
				break;
			case officerobj:
				NewState (ob,&s_ofcshoot1);
				break;
			case mutantobj:
				NewState (ob,&s_mutshoot1);
				break;
			case ssobj:
				NewState (ob,&s_ssshoot1);
				break;
#ifndef SPEAR
			case bossobj:
				NewState (ob,&s_bossshoot1);
				break;
			case gretelobj:
				NewState (ob,&s_gretelshoot1);
				break;
			case mechahitlerobj:
				NewState (ob,&s_mechashoot1);
				break;
			case realhitlerobj:
				NewState (ob,&s_hitlershoot1);
				break;
#else
			case angelobj:
				NewState (ob,&s_angelshoot1);
				break;
			case transobj:
				NewState (ob,&s_transshoot1);
				break;
			case uberobj:
				NewState (ob,&s_ubershoot1);
				break;
			case willobj:
				NewState (ob,&s_willshoot1);
				break;
			case deathobj:
				NewState (ob,&s_deathshoot1);
				break;
#endif
			}
			return;
		}
		dodge = TRUE;
	}

	if (ob->dir == nodir)
	{
		if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (ob->distance < 0)
		{
		//
		// waiting for a door to open
		//
			OpenDoor (-ob->distance-1);
			if (doorobjlist[-ob->distance-1].action != dr_open)
				return;
			ob->distance = TILEGLOBAL;	// go ahead, the door is now opoen
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		if (dodge)
			SelectDodgeDir (ob);
		else
			SelectChaseDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}


/*
=================
=
= T_Ghosts
=
=================
*/

void T_Ghosts (objtype *ob)
{
	s32 move;


	if (ob->dir == nodir)
	{
		SelectChaseDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		SelectChaseDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}

/*
=================
=
= T_DogChase
=
=================
*/

void T_DogChase (objtype *ob)
{
	s32 	move;
	s16		dist,chance;
	s32	dx,dy;


	if (ob->dir == nodir)
	{
		SelectDodgeDir (ob);
		if (ob->dir == nodir)
			return;							// object is blocked in
	}

	move = ob->speed*tics;

	while (move)
	{
	//
	// check for byte range
	//
		dx = player->x - ob->x;
		if (dx<0)
			dx = -dx;
		dx -= move;
		if (dx <= MINACTORDIST)
		{
			dy = player->y - ob->y;
			if (dy<0)
				dy = -dy;
			dy -= move;
			if (dy <= MINACTORDIST)
			{
				NewState (ob,&s_dogjump1);
				return;
			}
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		//
		// reached goal tile, so select another one
		//

		//
		// fix position to account for round off during moving
		//
		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;

		move -= ob->distance;

		SelectDodgeDir (ob);

		if (ob->dir == nodir)
			return;							// object is blocked in
	}

}



/*
============================================================================

								PATH

============================================================================
*/


/*
===============
=
= SelectPathDir
=
===============
*/

void SelectPathDir (objtype *ob)
{
	u16 spot;

	spot = InfoPlane(ob->tilex,ob->tiley)-ICONARROWS;

	if (spot<8)
	{
	// newobj direction
		ob->dir = spot;
	}

	ob->distance = TILEGLOBAL;

	if (!TryWalk (ob))
		ob->dir = nodir;
}


/*
===============
=
= T_Path
=
===============
*/

void T_Path (objtype *ob)
{
	s32 	move;
	s32 	deltax,deltay,size;

	if (SightPlayer (ob))
		return;

	if (ob->dir == nodir)
	{
		SelectPathDir (ob);
		if (ob->dir == nodir)
			return;					// all movement is blocked
	}


	move = ob->speed*tics;

	while (move)
	{
		if (ob->distance < 0)
		{
		//
		// waiting for a door to open
		//
			OpenDoor (-ob->distance-1);
			if (doorobjlist[-ob->distance-1].action != dr_open)
				return;
			ob->distance = TILEGLOBAL;	// go ahead, the door is now opoen
		}

		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}

		if (ob->tilex>MAPSIZE || ob->tiley>MAPSIZE)
		{
			Quit ("T_Path hit a wall");
		}



		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;
		move -= ob->distance;

		SelectPathDir (ob);

		if (ob->dir == nodir)
			return;					// all movement is blocked
	}
}


/*
=============================================================================

								FIGHT

=============================================================================
*/


/*
===============
=
= T_Shoot
=
= Try to damage the player, based on skill level and player's speed
=
===============
*/

void T_Shoot (objtype *ob)
{
	s16	dx,dy,dist;
	s16	hitchance,damage;

	hitchance = 128;

	if (!areabyplayer[ob->areanumber])
		return;

	if (!CheckLine (ob))			// player is behind a wall
	  return;

	dx = abs(ob->tilex - player->tilex);
	dy = abs(ob->tiley - player->tiley);
	dist = dx>dy ? dx:dy;

	if (ob->obclass == ssobj || ob->obclass == bossobj)
		dist = dist*2/3;					// ss are better shots

	if (thrustspeed >= RUNSPEED)
	{
		if (ob->flags&FL_VISABLE)
			hitchance = 160-dist*16;		// player can see to dodge
		else
			hitchance = 160-dist*8;
	}
	else
	{
		if (ob->flags&FL_VISABLE)
			hitchance = 256-dist*16;		// player can see to dodge
		else
			hitchance = 256-dist*8;
	}

// see if the shot was a hit

	if (US_RndT()<hitchance)
	{
		if (dist<2)
			damage = US_RndT()>>2;
		else if (dist<4)
			damage = US_RndT()>>3;
		else
			damage = US_RndT()>>4;

		TakeDamage (damage,ob);
	}

	switch(ob->obclass)
	{
	 case ssobj:
	   PlaySoundLocActor(SSFIRESND,ob);
	   break;
#ifndef SPEAR
	 case giftobj:
	 case fatobj:
	   PlaySoundLocActor(MISSILEFIRESND,ob);
	   break;
	 case mechahitlerobj:
	 case realhitlerobj:
	 case bossobj:
	   PlaySoundLocActor(BOSSFIRESND,ob);
	   break;
	 case schabbobj:
	   PlaySoundLocActor(SCHABBSTHROWSND,ob);
	   break;
	 case fakeobj:
	   PlaySoundLocActor(FLAMETHROWERSND,ob);
	   break;
#endif
	 default:
	   PlaySoundLocActor(NAZIFIRESND,ob);
	}

}


/*
===============
=
= T_Bite
=
===============
*/

void T_Bite (objtype *ob)
{
	s32	dx,dy;
	s16	hitchance,damage;


	PlaySoundLocActor(DOGATTACKSND,ob);	// JAB

	dx = player->x - ob->x;
	if (dx<0)
		dx = -dx;
	dx -= TILEGLOBAL;
	if (dx <= MINACTORDIST)
	{
		dy = player->y - ob->y;
		if (dy<0)
			dy = -dy;
		dy -= TILEGLOBAL;
		if (dy <= MINACTORDIST)
		{
		   if (US_RndT()<180)
		   {
			   TakeDamage (US_RndT()>>4,ob);
			   return;
		   }
		}
	}

	return;
}


#ifndef SPEAR
/*
============================================================================

							BJ VICTORY

============================================================================
*/


//
// BJ victory
//

void T_BJRun (objtype *ob);
void T_BJJump (objtype *ob);
void T_BJDone (objtype *ob);
void T_BJYell (objtype *ob);

void T_DeathCam (objtype *ob);

const statetype s_bjrun1 = {FALSE,SPR_BJ_W1,12,T_BJRun,NULL,&s_bjrun1s};
const statetype s_bjrun1s = {FALSE,SPR_BJ_W1,3, NULL,NULL,&s_bjrun2};
const statetype s_bjrun2 = {FALSE,SPR_BJ_W2,8,T_BJRun,NULL,&s_bjrun3};
const statetype s_bjrun3 = {FALSE,SPR_BJ_W3,12,T_BJRun,NULL,&s_bjrun3s};
const statetype s_bjrun3s = {FALSE,SPR_BJ_W3,3, NULL,NULL,&s_bjrun4};
const statetype s_bjrun4 = {FALSE,SPR_BJ_W4,8,T_BJRun,NULL,&s_bjrun1};


const statetype s_bjjump1 = {FALSE,SPR_BJ_JUMP1,14,T_BJJump,NULL,&s_bjjump2};
const statetype s_bjjump2 = {FALSE,SPR_BJ_JUMP2,14,T_BJJump,T_BJYell,&s_bjjump3};
const statetype s_bjjump3 = {FALSE,SPR_BJ_JUMP3,14,T_BJJump,NULL,&s_bjjump4};
const statetype s_bjjump4 = {FALSE,SPR_BJ_JUMP4,300,NULL,T_BJDone,&s_bjjump4};


const statetype s_deathcam = {FALSE,0,0,NULL,NULL,NULL};


/*
===============
=
= SpawnBJVictory
=
===============
*/

void SpawnBJVictory (void)
{
	u8 *map;
	u16 tile;

	SpawnNewObj (player->tilex,player->tiley+1,&s_bjrun1);
	newobj->x = player->x;
	newobj->y = player->y;
	newobj->obclass = bjobj;
	newobj->dir = north;
	newobj->temp1 = 6;			// tiles to run forward
}



/*
===============
=
= T_BJRun
=
===============
*/

void T_BJRun (objtype *ob)
{
	s32 	move;

	move = BJRUNSPEED*tics;

	while (move)
	{
		if (move < ob->distance)
		{
			MoveObj (ob,move);
			break;
		}


		ob->x = ((s32)ob->tilex<<TILESHIFT)+TILEGLOBAL/2;
		ob->y = ((s32)ob->tiley<<TILESHIFT)+TILEGLOBAL/2;
		move -= ob->distance;

		SelectPathDir (ob);

		if ( !(--ob->temp1) )
		{
			NewState (ob,&s_bjjump1);
			return;
		}
	}
}


/*
===============
=
= T_BJJump
=
===============
*/

void T_BJJump (objtype *ob)
{
	s32 	move;

	move = BJJUMPSPEED*tics;
	MoveObj (ob,move);
}


/*
===============
=
= T_BJYell
=
===============
*/

void T_BJYell (objtype *ob)
{
	PlaySoundLocActor(YEAHSND,ob);	// JAB
}


/*
===============
=
= T_BJDone
=
===============
*/


void T_BJDone (objtype *ob)
{
	playstate = ex_victorious;				// exit castle tile
}



//===========================================================================


/*
===============
=
= CheckPosition
=
===============
*/

boolean	CheckPosition (objtype *ob)
{
	s16	x,y,xl,yl,xh,yh;
	objtype *check;

	xl = (ob->x-PLAYERSIZE) >>TILESHIFT;
	yl = (ob->y-PLAYERSIZE) >>TILESHIFT;

	xh = (ob->x+PLAYERSIZE) >>TILESHIFT;
	yh = (ob->y+PLAYERSIZE) >>TILESHIFT;

	//
	// check for solid walls
	//
	for (y=yl;y<=yh;y++)
		for (x=xl;x<=xh;x++)
		{
			u8 a = actorat[x][y];
			if (a && !ACT_ISACTOR(a))
				return FALSE;
		}

	return TRUE;
}


/*
===============
=
= A_StartDeathCam
=
===============
*/

void	A_StartDeathCam (objtype *ob)
{
	s32	dx,dy;
	s32    xmove,ymove;
	s32	dist;
	s16		temp,i;

	FinishPaletteShifts ();

	vid_wait (100);

	if (gamestate.victoryflag)
	{
		playstate = ex_victorious;				// exit castle tile
		return;
	}

	gamestate.victoryflag = TRUE;
	DeathCamIntro ();

//
// line angle up exactly
//
	NewState (player,&s_deathcam);

	player->x = gamestate.killx;
	player->y = gamestate.killy;

	dx = ob->x - player->x;
	dy = player->y - ob->y;

	player->angle = AimAngle (dy,dx);

//
// try to position as close as possible without being in a wall
//
	dist = 0x14000l;
	do
	{
		xmove = FixedByFrac(dist,costable[player->angle]);
		ymove = -FixedByFrac(dist,sintable[player->angle]);

		player->x = ob->x - xmove;
		player->y = ob->y - ymove;
		dist += 0x1000;

	} while (!CheckPosition (player));
	plux = player->x >> UNSIGNEDSHIFT;			// scale to fit in u16
	pluy = player->y >> UNSIGNEDSHIFT;
	player->tilex = player->x >> TILESHIFT;		// scale to tile values
	player->tiley = player->y >> TILESHIFT;

//
// go back to the game
//
	fizzlein = TRUE;
	switch (ob->obclass)
	{
#ifndef SPEAR
	case schabbobj:
		NewState (ob,&s_schabbdeathcam);
		break;
	case realhitlerobj:
		NewState (ob,&s_hitlerdeathcam);
		break;
	case giftobj:
		NewState (ob,&s_giftdeathcam);
		break;
	case fatobj:
		NewState (ob,&s_fatdeathcam);
		break;
#endif
	}

}

#endif
