#ifndef __GENERATOR__
#define __GENERATOR__

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

extern Vect2D_u16 roomTileSize;

u16 getTileValue(s16 x, s16 y);
void freeCollisionMap();
void generateCollisionMap(const u8 map[][48]);

#endif//__GENERATOR__