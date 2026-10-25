#ifndef AUDIO_H
#define AUDIO_H
#include "../wl_types.h"
typedef struct { u32 adlib_ofs, adlib_len, digi_ofs, digi_len; u16 priority; } snd_t;
typedef struct { u32 ofs, len; } mus_t;
extern const u8 pcm_data[];
extern const snd_t snd_tab[87];
extern const u8 music_data[];
extern const mus_t music_tab[27];
#define PCM_RATE_HZ 16000
#define NUMSOUNDS_G 87
#define NUMSONGS_G 27
#endif
