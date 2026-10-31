#include "snd_dpcm2.h"

void SND_DPCM2_loadDriver(const bool waitReady) {}

void SND_DPCM2_unloadDriver(void) {}

bool SND_DPCM2_isPlaying(const u16 channel_mask) { return 0; }

void SND_DPCM2_startPlay(const u8 *sample, const u32 len, const SoundPCMChannel channel, const bool loop) {}

void SND_DPCM2_stopPlay(const SoundPCMChannel channel) {}

