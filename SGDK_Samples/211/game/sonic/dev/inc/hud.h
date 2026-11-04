#ifndef _HUD_H_
#define _HUD_H_

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

u16 HUD_init(u16 vramIndex);

void HUD_setVisibility(bool visible);
void HUD_handleInput(u16 value);


#endif // _HUD_H_
