#include "_genesis.h"
#include "sprite_eng.h"

void SPR_init(void) {}

void SPR_initEx(u16 vramSize) {}

void SPR_end(void) {}

bool SPR_isInitialized(void) { return 0; }

void SPR_reset(void) {}

Sprite*SPR_addSpriteEx(const SpriteDefinition* spriteDef, s16 x, s16 y, u16 attribut, u16 flag) { return 0; }

Sprite*SPR_addSprite(const SpriteDefinition* spriteDef, s16 x, s16 y, u16 attribut) { return 0; }

Sprite*SPR_addSpriteExSafe(const SpriteDefinition* spriteDef, s16 x, s16 y, u16 attribut, u16 flag) { return 0; }

Sprite*SPR_addSpriteSafe(const SpriteDefinition* spriteDef, s16 x, s16 y, u16 attribut) { return 0; }

void SPR_releaseSprite(Sprite* sprite) {}

u16 SPR_getNumActiveSprite(void) { return 0; }

u16 SPR_getUsedVDPSprite(void) { return 0; }

u16 SPR_getFreeVRAM(void) { return 0; }

u16 SPR_getLargestFreeVRAMBlock(void) { return 0; }

void SPR_enableVDPSpriteChecking() {}

void SPR_disableVDPSpriteChecking() {}

void SPR_defragVRAM(void) {}

u16**SPR_loadAllFrames(const SpriteDefinition* sprDef, u16 index, u16* totalNumTile) { return 0; }

bool SPR_setDefinition(Sprite* sprite, const SpriteDefinition* spriteDef) { return 0; }

s16 SPR_getPositionX(Sprite* sprite) { return 0; }

s16 SPR_getPositionY(Sprite* sprite) { return 0; }

void SPR_setPosition(Sprite* sprite, s16 x, s16 y) {}

void SPR_setHFlip(Sprite* sprite, bool value) {}

void SPR_setVFlip(Sprite* sprite, bool value) {}

void SPR_setPalette(Sprite* sprite, u16 value) {}

void SPR_setPriority(Sprite* sprite, bool value) {}

void SPR_setDepth(Sprite* sprite, s16 value) {}

void SPR_setZ(Sprite* sprite, s16 value) {}

void SPR_setAlwaysOnTop(Sprite* sprite) {}

void SPR_setAlwaysAtBottom(Sprite* sprite) {}

void SPR_setAnimAndFrame(Sprite* sprite, s16 anim, s16 frame) {}

void SPR_setAnim(Sprite* sprite, s16 anim) {}

void SPR_setFrame(Sprite* sprite, s16 frame) {}

void SPR_nextFrame(Sprite* sprite) {}

void SPR_setAutoAnimation(Sprite* sprite, bool value) {}

bool SPR_getAutoAnimation(Sprite* sprite) { return 0; }

void SPR_setAnimationLoop(Sprite* sprite, bool value) {}

bool SPR_isAnimationDone(Sprite* sprite) { return 0; }

bool SPR_setVRAMTileIndex(Sprite* sprite, s16 value) { return 0; }

void SPR_setAutoTileUpload(Sprite* sprite, bool value) {}

void SPR_setDelayedFrameUpdate(Sprite* sprite, bool value) {}

void SPR_setFrameChangeCallback(Sprite* sprite, FrameChangeCallback* callback) {}

SpriteVisibility SPR_getVisibility(Sprite* sprite) { return 0; }

bool SPR_isVisible(Sprite* sprite, bool recompute) { return 0; }

void SPR_setVisibility(Sprite* sprite, SpriteVisibility value) {}

void SPR_clear(void) {}

void SPR_update(void) {}

void SPR_logProfil(void) {}

void SPR_logSprites(void) {}

