#ifndef __MAIN__
#define __MAIN__

#ifdef _CONSOLE
#include "_genesis.h"
#include "kdebug.h"
#pragma warning( disable : 4244 ) 
#else
#include <genesis.h>
#include <kdebug.h>
#define ENABLE_ASM
#endif

// end of bss
extern u32 _bend;

#include "gfx.h"
#include "spr_res.h"

#include "camera.h"
#include "level.h"

#endif//__MAIN__