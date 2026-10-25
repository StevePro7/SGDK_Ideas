#include "bmp.h"

void BMP_init(u16 double_buffer, VDPPlane plane, u16 palette, u16 priority) {}

void BMP_end(void) {}

void BMP_reset(void) {}

void BMP_setBufferCopy(u16 value) {}

u16 BMP_flip(u16 async) { return 0; }

void BMP_clear(void) {}

u8*BMP_getWritePointer(u16 x, u16 y) { return 0; }

u8*BMP_getReadPointer(u16 x, u16 y) { return 0; }

u16 BMP_hasFlipRequestPending(void) { return 0; }

void BMP_waitWhileFlipRequestPending(void) {}

u16 BMP_hasFlipInProgess(void) { return 0; }

void BMP_waitFlipComplete(void) {}

void BMP_drawText(const char *str, u16 x, u16 y) {}

void BMP_clearText(u16 x, u16 y, u16 w) {}

void BMP_clearTextLine(u16 y) {}

void BMP_showFPS(u16 float_display, u16 x, u16 y) {}

u8 BMP_getPixel(u16 x, u16 y) { return 0; }

u8 BMP_getPixelFast(u16 x, u16 y) { return 0; }

void BMP_setPixel(u16 x, u16 y, u8 col) {}

void BMP_setPixelFast(u16 x, u16 y, u8 col) {}

void BMP_setPixels_V2D(const Vect2D_u16 *crd, u8 col, u16 num) {}

void BMP_setPixelsFast_V2D(const Vect2D_u16 *crd, u8 col, u16 num) {}

void BMP_setPixels(const Pixel *pixels, u16 num) {}

void BMP_setPixelsFast(const Pixel *pixels, u16 num) {}

u16 BMP_clipLine(Line *l) { return 0; }

void BMP_drawLine(Line *l) {}

u16 BMP_isPolygonCulled(const Vect2D_s16 *pts, u16 num) { return 0; }

u16 BMP_drawPolygon(const Vect2D_s16 *pts, u16 num, u8 col) { return 0; }

void BMP_drawBitmapData(const u8 *data, u16 x, u16 y, u16 w, u16 h, u32 pitch) {}

bool BMP_drawBitmap(const Bitmap *bitmap, u16 x, u16 y, bool loadpal) { return 0; }

bool BMP_drawBitmapScaled(const Bitmap *bitmap, u16 x, u16 y, u16 w, u16 h, bool loadpal) { return 0; }

void BMP_scale(const u8 *src_buf, u16 src_wb, u16 src_h, u16 src_pitch, u8 *dst_buf, u16 dst_wb, u16 dst_h, u16 dst_pitch) {}

