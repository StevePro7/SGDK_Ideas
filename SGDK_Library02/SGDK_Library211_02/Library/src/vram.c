#include "vram.h"

void VRAM_createRegion(VRAMRegion *region, u16 startIndex, u16 size) {}

void VRAM_releaseRegion(VRAMRegion *region) {}

void VRAM_clearRegion(VRAMRegion *region) {}

u16 VRAM_getFree(VRAMRegion *region) { return 0; }

u16 VRAM_getAllocated(VRAMRegion *region) { return 0; }

u16 VRAM_getLargestFreeBlock(VRAMRegion *region) { return 0; }

s16 VRAM_alloc(VRAMRegion *region, u16 size) { return 0; }

void VRAM_free(VRAMRegion *region, u16 index) {}

