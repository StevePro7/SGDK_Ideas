#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

void engine_font_manager_data( u16 value, u16 x, u16 y );

#endif//_FONT_MANAGER_H_