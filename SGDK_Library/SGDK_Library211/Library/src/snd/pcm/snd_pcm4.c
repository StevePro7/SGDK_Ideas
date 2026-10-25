#include "_genesis.h"
#include "snd_pcm4.h"

void SND_PCM4_loadDriver(const bool waitReady) {}

void SND_PCM4_unloadDriver(void) {}

bool SND_PCM4_isPlaying(const u16 channel_mask) { return 0; }

void SND_PCM4_startPlay(const u8 *sample, const u32 len, const SoundPCMChannel channel, const bool loop) {}

void SND_PCM4_stopPlay(const SoundPCMChannel channel) {}

void SND_PCM4_setVolume(const SoundPCMChannel channel, const u8 volume) {}

u8 SND_PCM4_getVolume(const SoundPCMChannel channel) { return 0; }

