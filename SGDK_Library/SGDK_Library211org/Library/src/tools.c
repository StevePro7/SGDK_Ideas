#include "_genesis.h"
#include "tools.h"

void setRandomSeed(u16 seed) {}

u16 random(void) { return 0; }

int kprintf(const char *fmt, ...) { return 0; }

void KLog(char* text) {}

void KLog_U1(char* t1, u32 v1) {}

void KLog_U2(char* t1, u32 v1, char* t2, u32 v2) {}

void KLog_U3(char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3) {}

void KLog_U4(char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4, u32 v4) {}

void KLog_U1_(char* t1, u32 v1, char* t2) {}

void KLog_U2_(char* t1, u32 v1, char* t2, u32 v2, char* t3) {}

void KLog_U3_(char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4) {}

void KLog_U4_(char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4, u32 v4, char* t5) {}

void KLog_U1x(u16 minSize, char* t1, u32 v1) {}

void KLog_U2x(u16 minSize, char* t1, u32 v1, char* t2, u32 v2) {}

void KLog_U3x(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3) {}

void KLog_U4x(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4, u32 v4) {}

void KLog_U1x_(u16 minSize, char* t1, u32 v1, char* t2) {}

void KLog_U2x_(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3) {}

void KLog_U3x_(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4) {}

void KLog_U4x_(u16 minSize, char* t1, u32 v1, char* t2, u32 v2, char* t3, u32 v3, char* t4, u32 v4, char* t5) {}

void KLog_S1(char* t1, s32 v1) {}

void KLog_S2(char* t1, s32 v1, char* t2, s32 v2) {}

void KLog_S3(char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3) {}

void KLog_S4(char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3, char* t4, s32 v4) {}

void KLog_S1_(char* t1, s32 v1, char* t2) {}

void KLog_S2_(char* t1, s32 v1, char* t2, s32 v2, char* t3) {}

void KLog_S3_(char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3, char* t4) {}

void KLog_S4_(char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3, char* t4, s32 v4, char* t5) {}

void KLog_S1x(u16 minSize, char* t1, s32 v1) {}

void KLog_S2x(u16 minSize, char* t1, s32 v1, char* t2, s32 v2) {}

void KLog_S3x(u16 minSize, char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3) {}

void KLog_S4x(u16 minSize, char* t1, s32 v1, char* t2, s32 v2, char* t3, s32 v3, char* t4, s32 v4) {}

void KLog_f1(char* t1, fix16 v1) {}

void KLog_f2(char* t1, fix16 v1, char* t2, fix16 v2) {}

void KLog_f3(char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3) {}

void KLog_f4(char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3, char* t4, fix16 v4) {}

void KLog_f1x(s16 numDec, char* t1, fix16 v1) {}

void KLog_f2x(s16 numDec, char* t1, fix16 v1, char* t2, fix16 v2) {}

void KLog_f3x(s16 numDec, char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3) {}

void KLog_f4x(s16 numDec, char* t1, fix16 v1, char* t2, fix16 v2, char* t3, fix16 v3, char* t4, fix16 v4) {}

void KLog_F1(char* t1, fix32 v1) {}

void KLog_F2(char* t1, fix32 v1, char* t2, fix32 v2) {}

void KLog_F3(char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3) {}

void KLog_F4(char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3, char* t4, fix32 v4) {}

void KLog_F1x(s16 numDec, char* t1, fix32 v1) {}

void KLog_F2x(s16 numDec, char* t1, fix32 v1, char* t2, fix32 v2) {}

void KLog_F3x(s16 numDec, char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3) {}

void KLog_F4x(s16 numDec, char* t1, fix32 v1, char* t2, fix32 v2, char* t3, fix32 v3, char* t4, fix32 v4) {}

Bitmap *allocateBitmap(const Bitmap *bitmap) { return 0; }

Bitmap *allocateBitmapEx(u16 width, u16 heigth) { return 0; }

TileSet *allocateTileSet(const TileSet *tileset) { return 0; }

TileSet *allocateTileSetEx(u16 numTile) { return 0; }

TileMap *allocateTileMap(const TileMap *tilemap) { return 0; }

TileMap *allocateTileMapEx(u16 width, u16 heigth) { return 0; }

Image *allocateImage(const Image *image) { return 0; }

Map *allocateMap(const MapDefinition *mapDef) { return 0; }

Bitmap *unpackBitmap(const Bitmap *src, Bitmap *dest) { return 0; }

TileSet *unpackTileSet(const TileSet *src, TileSet *dest) { return 0; }

TileMap *unpackTileMap(const TileMap *src, TileMap *dest) { return 0; }

Image *unpackImage(const Image *src, Image *dest) { return 0; }

u32 unpack(u16 compression, u8 *src, u8 *dest) { return 0; }

u32 aplib_unpack(u8 *src, u8 *dest) { return 0; }

u32 lz4w_unpack(const u8 *src, u8 *dest) { return 0; }

void qsort_u8(u8 *data, u16 left, u16 right) {}

void qsort_s8(s8 *data, u16 left, u16 right) {}

void qsort_u16(u16 *data, u16 left, u16 right) {}

void qsort_s16(s16 *data, u16 left, u16 right) {}

void qsort_u32(u32 *data, u16 left, u16 right) {}

void qsort_s32(s32 *data, u16 left, u16 right) {}

void qsort(void** data, u16 len, _comparatorCallback* cb) {}

