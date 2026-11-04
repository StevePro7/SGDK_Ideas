#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

void setSpritePosition(Sprite* sprite, s16 x, s16 y);

#endif // _UTILS_H_
