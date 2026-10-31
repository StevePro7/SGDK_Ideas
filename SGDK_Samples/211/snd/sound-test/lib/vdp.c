#include "vdp.h"

u16 window_addr = 0;
u16 bga_addr = 0;
u16 bgb_addr = 0;
u16 hscrl_addr = 0;
u16 slist_addr = 0;
u16 maps_addr = 0;
u16 userTileMaxIndex = 0;
u16 screenWidth = 0;
u16 screenHeight = 0;
u16 planeWidth = 0;
u16 planeHeight = 0;
u16 windowWidth = 0;
u16 planeWidthSft = 0;
u16 planeHeightSft = 0;
u16 windowWidthSft = 0;

void VDP_init(void) {}

void VDP_resetScreen(void) {}

u8 VDP_getReg(u16 reg) { return 0; }

void VDP_setReg(u16 reg, u8 value) {}

bool VDP_getEnable(void) { return 0; }

bool VDP_isEnable(void) { return 0; }

void VDP_setEnable(bool value) {}

u16 VDP_getScanlineNumber(void) { return 0; }

u16 VDP_getScreenHeight(void) { return 0; }

void VDP_setScreenHeight224(void) {}

void VDP_setScreenHeight240(void) {}

u16 VDP_getScreenWidth(void) { return 0; }

void VDP_setScreenWidth256(void) {}

void VDP_setScreenWidth320(void) {}

u16 VDP_getPlaneWidth(void) { return 0; }

u16 VDP_getPlaneHeight(void) { return 0; }

void VDP_setPlaneSize(u16 w, u16 h, bool setupVram) {}

u8 VDP_getHorizontalScrollingMode(void) { return 0; }

u8 VDP_getVerticalScrollingMode(void) { return 0; }

void VDP_setScrollingMode(u16 hscroll, u16 vscroll) {}

u8 VDP_getBackgroundColor(void) { return 0; }

void VDP_setBackgroundColor(u8 value) {}

u8 VDP_getAutoInc(void) { return 0; }

void VDP_setAutoInc(u8 value) {}

u8 VDP_getDMAEnabled(void) { return 0; }

void VDP_setDMAEnabled(bool value) {}

u8 VDP_getHVLatching(void) { return 0; }

void VDP_setHVLatching(bool value) {}

void VDP_setVInterrupt(bool value) {}

void VDP_setHInterrupt(bool value) {}

void VDP_setExtInterrupt(bool value) {}

void VDP_setHilightShadow(bool value) {}

u8 VDP_getHIntCounter(void) { return 0; }

void VDP_setHIntCounter(u8 value) {}

u16 VDP_getBGAAddress(void) { return 0; }

u16 VDP_getBGBAddress(void) { return 0; }

u16 VDP_getWindowAddress(void) { return 0; }

u16 VDP_getSpriteListAddress(void) { return 0; }

u16 VDP_getHScrollTableAddress(void) { return 0; }

void VDP_setBGAAddress(u16 value) {}

void VDP_setBGBAddress(u16 value) {}

void VDP_setWindowAddress(u16 value) {}

void VDP_setSpriteListAddress(u16 value) {}

void VDP_setHScrollTableAddress(u16 value) {}

void VDP_setScanMode(u16 mode) {}

void VDP_setWindowHPos(u16 right, u16 pos) {}

void VDP_setWindowVPos(u16 down, u16 pos) {}

void VDP_setWindowOff() {}

void VDP_setWindowOnTop(u16 rows) {}

void VDP_setWindowOnBottom(u16 rows) {}

void VDP_setWindowOnLeft(u16 cols) {}

void VDP_setWindowOnRight(u16 cols) {}

void VDP_setWindowFullScreen() {}

void VDP_waitDMACompletion(void) {}

void VDP_waitFIFOEmpty(void) {}

bool VDP_waitVInt(void) { return 0; }

bool VDP_waitVBlank(bool forceNext) { return 0; }

bool VDP_waitVSync(void) { return 0; }

void VDP_waitVActive(bool forceNext) {}

u16 VDP_getAdjustedVCounter(void) { return 0; }

void VDP_showFPS(u16 asFloat, u16 x, u16 y) {}

void VDP_showCPULoad(u16 x, u16 y) {}

