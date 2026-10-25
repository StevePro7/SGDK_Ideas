#include "snd_pcm.h"

void SND_PCM_loadDriver(const bool waitReady) {}

void SND_PCM_unloadDriver(void) {}

bool SND_PCM_isPlaying(void) { return 0; }

void SND_PCM_startPlay(const u8 *sample, const u32 len, const SoundPcmSampleRate rate, const SoundPanning pan, const bool loop) {}

void SND_PCM_stopPlay(void) {}

