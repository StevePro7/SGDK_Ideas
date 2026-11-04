#ifndef _ENTITIES_H_
#define _ENTITIES_H_

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

u16 ENTITIES_init(u16 vramIndex);

void ENTITIES_update(void);
void ENTITIES_updateScreenPosition();


#endif // _ENTITIES_H_
