#include "pal.h"

const u16* const palette_black = NULL;
const u16 palette_grey[16] = { 0 };
const u16 palette_red[16] = { 0 };
const u16 palette_green[16] = { 0 };
const u16 palette_blue[16] = { 0 };
u16 fadeCurrentPal[64] = { 0 };
u16 fadeEndPal[64] = { 0 };

u16 PAL_getColor(u16 index) { return 0; }

void PAL_getColors(u16 index, u16* dest, u16 count) {}

void PAL_getPalette(u16 numPal, u16* dest) {}

void PAL_setColor(u16 index, u16 value) {}

void PAL_setColors(u16 index, const u16* pal, u16 count, TransferMethod tm) {}

void PAL_setPaletteColors(u16 index, const Palette* pal, TransferMethod tm) {}

void PAL_setPalette(u16 numPal, const u16* pal, TransferMethod tm) {}

bool PAL_initFade(u16 fromCol, u16 toCol, const u16* palSrc, const u16* palDst, u16 numFrame) { return 0; }

bool PAL_doFadeStep(void) { return 0; }

bool PAL_isManualFadeDone(void) { return 0; }

void PAL_fade(u16 fromCol, u16 toCol, const u16* palSrc, const u16* palDst, u16 numFrame, bool async) {}

void PAL_fadeTo(u16 fromCol, u16 toCol, const u16* pal, u16 numFrame, bool async) {}

void PAL_fadeOut(u16 fromCol, u16 toCol, u16 numFrame, bool async) {}

void PAL_fadeIn(u16 fromCol, u16 toCol, const u16* pal, u16 numFrame, bool async) {}

void PAL_fadePalette(u16 numPal, const u16* palSrc, const u16* palDst, u16 numFrame, bool async) {}

void PAL_fadeToPalette(u16 numPal, const u16* pal, u16 numFrame, bool async) {}

void PAL_fadeOutPalette(u16 numPal, u16 numFrame, bool async) {}

void PAL_fadeInPalette(u16 numPal, const u16* pal, u16 numFrame, bool async) {}

void PAL_fadeAll(const u16* palSrc, const u16* palDst, u16 numFrame, bool async) {}

void PAL_fadeToAll(const u16* pal, u16 numFrame, bool async) {}

void PAL_fadeOutAll(u16 numFrame, bool async) {}

void PAL_fadeInAll(const u16* pal, u16 numFrame, bool async) {}

bool PAL_isDoingFade(void) { return 0; }

void PAL_waitFadeCompletion(void) {}

void PAL_interruptFade(void) {}

