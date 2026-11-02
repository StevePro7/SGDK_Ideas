#ifndef XGM_TOOL_H
#define XGM_TOOL_H

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

#include "psg_state.h"
#include "ym_state.h"

typedef struct
{
	char *trackName;
	char *gameName;
	char *authorName;
	char *date;
	char *conversionAuthor;
	char *notes;
	u32 duration;
	u32 loopDuration;
} XD3;

extern vs16 frameToParse;

s32 XD3_getDuration( XD3* xd3, s16 loopCnt );

u32 XGM_getMusicDataOffset(const u8* xgm);
//u32 XGM_getDuration(const u8* xgm, s16 loopCnt);
void XGM_getXD3(const u8* xgm, XD3* xd3);

s32 XGM_parseFrame(u8* frameData, YM* ym, PSG *psg);


#endif // XGM_TOOL_H
