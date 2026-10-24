#include "_genesis.h"
#include "joy.h"

void JOY_init(void) {}

void JOY_reset(void) {}

JoyEventCallback*JOY_getEventHandler() { return 0; }

void JOY_setEventHandler(JoyEventCallback *CB) {}

void JOY_setSupport(u16 port, u16 support) {}

u8 JOY_getPortType(u16 port) { return 0; }

u8 JOY_getJoypadType(u16 joy) { return 0; }

u16 JOY_readJoypad(u16 joy) { return 0; }

s16 JOY_readJoypadX(u16 joy) { return 0; }

s16 JOY_writeJoypadX(u16 joy, u16 pos) { return 0; }

s16 JOY_readJoypadY(u16 joy) { return 0; }

s16 JOY_writeJoypadY(u16 joy, u16 pos) { return 0; }

void JOY_waitPressBtn(void) {}

u16 JOY_waitPressBtnTime(u16 ms) { return 0; }

u16 JOY_waitPress(u16 joy, u16 btn) { return 0; }

u16 JOY_waitPressTime(u16 joy, u16 btn, u16 ms) { return 0; }

void JOY_update(void) {}

