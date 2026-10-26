#ifndef SND_H
#define SND_H
#include "wl_types.h"
typedef enum { sds_Off, sds_PC, sds_SoundSource, sds_SoundBlaster } SDSMode;
extern SDSMode DigiMode;
extern boolean SoundOn, MusicOn;
void SD_Init(void);
void snd_tick(void);
boolean SD_PlaySound(u16 sound);
void SD_StopSound(void);
void SD_WaitSoundDone(void);
u16 SD_SoundPlaying(void);
void SD_PositionSound(s16 leftvol, s16 rightvol);
void SD_SetPosition(s16 leftvol, s16 rightvol);
boolean SD_SoundPositioned(void);
void SD_StartMusic(u16 song);
void SD_StartLevelMusic(u16 song);
void SD_MusicOff(void);
void SD_FadeOutMusic(void);
#endif
