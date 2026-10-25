#include "mapper.h"

void SYS_resetBanks() {}

u16 SYS_getBank(u16 regionIndex) { return 0; }

void SYS_setBank(u16 regionIndex, u16 bankIndex) {}

void*SYS_getFarData(void* data) { return 0; }

void*SYS_getFarDataEx(void* data, bool high) { return 0; }

bool SYS_isCrossingBank(void* data, u32 size) { return 0; }

void*SYS_getFarDataSafe(void* data, u32 size) { return 0; }

void*SYS_getFarDataSafeEx(void* data, u32 size, bool high) { return 0; }

bool SYS_getNextFarAccessRegion() { return 0; }

void SYS_setNextFarAccessRegion(bool high) {}

