#include "_genesis.h"
#include "z80_ctrl.h"

void Z80_init(void) {}

bool Z80_isBusTaken(void) { return 0; }

void Z80_requestBus(bool wait) {}

bool Z80_getAndRequestBus(bool wait) { return 0; }

void Z80_releaseBus(void) {}

void Z80_startReset(void) {}

void Z80_endReset(void) {}

void Z80_setBank(const u16 bank) {}

u8 Z80_read(const u16 addr) { return 0; }

void Z80_write(const u16 addr, const u8 value) {}

void Z80_clear(void) {}

void Z80_upload(const u16 dest, const u8 *data, const u16 size) {}

void Z80_download(const u16 from, u8 *dest, const u16 size) {}

u16 Z80_getLoadedDriver(void) { return 0; }

void Z80_unloadDriver(void) {}

void Z80_loadDriver(const u16 driver, const bool waitReady) {}

void Z80_loadCustomDriver(const u8 *drv, u16 size) {}

bool Z80_isDriverReady(void) { return 0; }

void Z80_useBusProtection(u16 signalAddress) {}

void Z80_setBusProtection(bool value) {}

void Z80_enableBusProtection() {}

void Z80_disableBusProtection() {}

bool Z80_getForceDelayDMA(void) { return 0; }

void Z80_setForceDelayDMA(bool value) {}

