#include "vdp_spr.h"

void VDP_resetSprites(void) {}

void VDP_releaseAllSprites(void) {}

s16 VDP_allocateSprites(u16 num) { return 0; }

void VDP_releaseSprites(u16 index, u16 num) {}

u16 VDP_getAvailableSprites(void) { return 0; }

s16 VDP_refreshHighestAllocatedSpriteIndex(void) { return 0; }

void VDP_clearSprites(void) {}

void VDP_setSpriteFull(u16 index, s16 x, s16 y, u8 size, u16 attribut, u8 link) {}

void VDP_setSprite(u16 index, s16 x, s16 y, u8 size, u16 attribut) {}

void VDP_setSpritePosition(u16 index, s16 x, s16 y) {}

void VDP_setSpriteSize(u16 index, u8 size) {}

void VDP_setSpriteAttribut(u16 index, u16 attribut) {}

void VDP_setSpriteLink(u16 index, u8 link) {}

VDPSprite*VDP_linkSprites(u16 index, u16 num) { return 0; }

void VDP_updateSprites(u16 num, TransferMethod tm) {}

void VDP_setSpritePriority(u16 index, bool priority) {}

bool VDP_getSpritePriority(u16 index) { return 0; }

void VDP_setSpritePalette(u16 index, u16 palette) {}

u16 VDP_getSpritePalette(u16 index) { return 0; }

void VDP_setSpriteFlip(u16 index, bool flipH, bool flipV) {}

void VDP_setSpriteFlipH(u16 index, bool flipH) {}

void VDP_setSpriteFlipV(u16 index, bool flipV) {}

bool VDP_getSpriteFlipH(u16 index) { return 0; }

bool VDP_getSpriteFlipV(u16 index) { return 0; }

void VDP_setSpriteTile(u16 index, u16 tile) {}

u16 VDP_getSpriteTile(u16 index) { return 0; }

