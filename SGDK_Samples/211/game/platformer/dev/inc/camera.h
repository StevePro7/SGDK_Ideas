#ifndef __CAMERA__
#define __CAMERA__

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

#include "xtypes.h"
#include "player.h"
#include "physics.h"
#include "levels.h"

extern Vect2D_s16 cameraPosition;

void setupCamera(Vect2D_u16 deadZoneCenter, u16 deadZoneWidth, u16 deadZoneHeight);
void updateCamera();

#endif//__CAMERA__