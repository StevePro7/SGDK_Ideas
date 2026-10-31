#include "xgm.h"

void XGM_loadDriver(const bool waitReady) {}

void XGM_unloadDriver(void) {}

bool XGM_isPlaying(void) { return 0; }

void XGM_startPlay(const u8 *song) {}

void XGM_startPlay_FAR(const u8 *song, u32 size) {}

void XGM_stopPlay(void) {}

void XGM_pausePlay(void) {}

void XGM_resumePlay(void) {}

u8 XGM_isPlayingPCM(const u16 channel_mask) { return 0; }

void XGM_setPCM(const u8 id, const u8 *sample, const u32 len) {}

void XGM_setPCMFast(const u8 id, const u8 *sample, const u32 len) {}

void XGM_setPCM_FAR(const u8 id, const u8 *sample, const u32 len) {}

void XGM_setPCMFast_FAR(const u8 id, const u8 *sample, const u32 len) {}

void XGM_startPlayPCM(const u8 id, const u8 priority, const SoundPCMChannel channel) {}

void XGM_stopPlayPCM(const SoundPCMChannel channel) {}

u32 XGM_getElapsed(void) { return 0; }

u16 XGM_getMusicTempo(void) { return 0; }

void XGM_setMusicTempo(const u16 value) {}

u16 XGM_getManualSync(void) { return 0; }

void XGM_setManualSync(const bool value) {}

void XGM_nextXFrame(const u16 num) {}

void XGM_setLoopNumber(const s8 value) {}

void XGM_set68KBUSProtection(const bool value) {}

bool XGM_getForceDelayDMA(void) { return 0; }

void XGM_setForceDelayDMA(const bool value) {}

u32 XGM_getCPULoad(void) { return 0; }

