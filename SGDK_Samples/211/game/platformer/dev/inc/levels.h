#ifndef __LEVELS__
#define __LEVELS__

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

#include "map.h"
//#include "global.h"
//#include "xtypes.h"

typedef struct {
	s8 top;
	s8 bottom;
	s8 left;
	s8 right;
}Level;

void loadLevel();

extern u16 currentCurrencySpawnerEntity;

#endif//__LEVELS__