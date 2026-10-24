#include "_genesis.h"
#include "xgm2.h"

void XGM2_loadDriver(bool waitReady) {}

void XGM2_unloadDriver(void) {}

bool XGM2_isPlaying(void) { return 0; }

void XGM2_load(const u8 *song) {}

void XGM2_load_FAR(const u8 *song, const u32 len) {}

void XGM2_playTrack(const u16 track) {}

void XGM2_play(const u8* song) {}

void XGM2_play_FAR(const u8* song, const u32 len) {}

void XGM2_stop(void) {}

void XGM2_pause(void) {}

void XGM2_resume(void) {}

u8 XGM2_isPlayingPCM(const u16 channel_mask) { return 0; }

bool XGM2_playPCM(const u8 *sample, const u32 len, const SoundPCMChannel channel) { return 0; }

bool XGM2_playPCMEx(const u8 *sample, const u32 len, const SoundPCMChannel channel, const u8 priority, const bool halfRate, const bool loop) { return 0; }

void XGM2_stopPCM(const SoundPCMChannel channel) {}

bool XGM2_isProcessingFade(void) { return 0; }

void XGM2_fadeIn(const u16 numFrame) {}

void XGM2_fadeOut(const u16 numFrame) {}

void XGM2_fadeOutAndStop(const u16 numFrame) {}

void XGM2_fadeOutAndPause(const u16 numFrame) {}

void XGM2_fadeTo(const u16 fmVolume, const u16 psgVolume, const u16 numFrame) {}

void XGM2_setLoopNumber(const s8 value) {}

u32 XGM2_getElapsed(void) { return 0; }

u16 XGM2_getMusicTempo(void) { return 0; }

void XGM2_setMusicTempo(const u16 value) {}

void XGM2_setFMVolume(const u16 value) {}

void XGM2_setPSGVolume(const u16 value) {}

bool XGM2_isPAL(const u8 *xgm2) { return 0; }

u16 XGM2_getCPULoad(const bool mean) { return 0; }

u16 XGM2_getDMAWaitTime(const bool mean) { return 0; }

u16 XGM2_getDebugFrameCounter(void) { return 0; }

u16 XGM2_getDebugPCMRate(void) { return 0; }

u8 XGM2_getDebugMissedFrames(void) { return 0; }

u8 XGM2_getDebugProcessDuration(const u16 ind) { return 0; }

