#ifndef GEN_H
#define GEN_H
#include "wl_types.h"
#define VIEWW 256
#define VIEWH 128
#define NUMWALLPAGES 106
#define NUMSPRITES 436
#define NUMMAPS 10
#define FLOOR_PALIDX 0
#define CEIL_PALIDX 1
typedef struct { u32 data_ofs; u16 colidx; u8 left, right; } sprhdr_t;
typedef struct { const u8 *p0; const u16 *p1; const char *name; u16 ceilcolor; s32 partics; } mapinfo_t;
extern const s32 sintable[450];
extern const s32 finetangent[900];
extern const s16 pixelangle[128];
extern const u8 rndtable[256];
extern const u32 recip_step[513];
extern const s32 proj_scale, proj_heightnumerator;
extern const u32 scaler_ofs[];
extern const u16 scaler_code[];
extern const u32 wall_ofs[NUMWALLPAGES];
extern const u8 wall_data[];
extern const sprhdr_t spr_hdr[NUMSPRITES];
extern const u16 spr_colofs[];
extern const u8 spr_data[];
extern const mapinfo_t mapinfo[NUMMAPS];
extern const u16 view_palette[16];
#endif
