#include "_genesis.h"
#include "vdp_bg.h"

void VDP_setHorizontalScroll(VDPPlane plane, s16 value) {}

void VDP_setHorizontalScrollVSync(VDPPlane plane, s16 value) {}

void VDP_setHorizontalScrollTile(VDPPlane plane, u16 tile, s16* values, u16 len, TransferMethod tm) {}

void VDP_setHorizontalScrollLine(VDPPlane plane, u16 line, s16* values, u16 len, TransferMethod tm) {}

void VDP_setVerticalScroll(VDPPlane plane, s16 value) {}

void VDP_setVerticalScrollVSync(VDPPlane plane, s16 value) {}

void VDP_setVerticalScrollTile(VDPPlane plane, u16 tile, s16* values, u16 len, TransferMethod tm) {}

void VDP_clearPlane(VDPPlane plane, bool wait) {}

VDPPlane VDP_getTextPlane(void) { return 0; }

u16 VDP_getTextPalette(void) { return 0; }

u16 VDP_getTextPriority(void) { return 0; }

void VDP_setTextPlane(VDPPlane plane) {}

void VDP_setTextPalette(u16 palette) {}

void VDP_setTextPriority(u16 prio) {}

void VDP_drawTextEx(VDPPlane plane, const char* str, u16 basetile, u16 x, u16 y, TransferMethod tm) {}

void VDP_clearTextEx(VDPPlane plane, u16 basetile, u16 x, u16 y, u16 w, TransferMethod tm) {}

void VDP_clearTextAreaEx(VDPPlane plane, u16 basetile, u16 x, u16 y, u16 w, u16 h, TransferMethod tm) {}

void VDP_drawTextBG(VDPPlane plane, const char* str, u16 x, u16 y) {}

void VDP_clearTextBG(VDPPlane plane, u16 x, u16 y, u16 w) {}

void VDP_clearTextAreaBG(VDPPlane plane, u16 x, u16 y, u16 w, u16 h) {}

void VDP_clearTextLineBG(VDPPlane plane, u16 y) {}

void VDP_drawText(const char* str, u16 x, u16 y) {}

void VDP_drawTextBGFill(VDPPlane plane, const char* str, u16 x, u16 y, u16 len) {}

void VDP_drawTextFill(const char* str, u16 x, u16 y, u16 len) {}

void VDP_clearText(u16 x, u16 y, u16 w) {}

void VDP_clearTextArea(u16 x, u16 y, u16 w, u16 h) {}

void VDP_clearTextLine(u16 y) {}

bool VDP_drawBitmap(VDPPlane plane, const Bitmap *bitmap, u16 x, u16 y) { return 0; }

bool VDP_drawBitmapEx(VDPPlane plane, const Bitmap *bitmap, u16 basetile, u16 x, u16 y, bool loadpal) { return 0; }

bool VDP_drawImage(VDPPlane plane, const Image *image, u16 x, u16 y) { return 0; }

bool VDP_drawImageEx(VDPPlane plane, const Image *image, u16 basetile, u16 x, u16 y, bool loadpal, bool dma) { return 0; }

