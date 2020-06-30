#ifndef __MAIN__
#define __MAIN__

#ifdef _CONSOLE
#include "_genesis.h"
#include "smp_null.h"
#pragma warning( disable : 4244 )
#else
#include <genesis.h>
#include "smp_null.h"
#endif

#include "gfx.h"
#include "music.h"

#include "log_tab.h"
#include "psg_state.h"
#include "tracklist.h"
#include "xd3.h"
#include "xgm_tool.h"
#include "ym_state.h"

// get access to XGM driver timer
//extern s16 xgmTempoCnt;

#endif//__MAIN__