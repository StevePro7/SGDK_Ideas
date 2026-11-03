#ifndef __MAP__
#define __MAP__

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

extern const Vect2D_s16 levelStartPos;

extern const u8 collisionMap[48][48];

#endif//__MAP__