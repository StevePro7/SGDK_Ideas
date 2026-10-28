#include "_genesis.h"
#include "ym2612.h"

void YM2612_reset(void) {}

u8 YM2612_read(const u16 port) { return 0; }

u8 YM2612_readStatus() { return 0; }

void YM2612_write(const u16 port, const u8 data) {}

void YM2612_writeReg(const u16 part, const u8 reg, const u8 data) {}

void YM2612_enableDAC(void) {}

void YM2612_disableDAC(void) {}

