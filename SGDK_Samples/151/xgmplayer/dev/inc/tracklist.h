#ifndef TRACKLIST_H
#define TRACKLIST_H

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif


#define MAX_MUSIC           100

extern const u16 NUM_MUSIC;
extern const u8* const xgm_musics[MAX_MUSIC];


#endif // TRACKLIST_H
