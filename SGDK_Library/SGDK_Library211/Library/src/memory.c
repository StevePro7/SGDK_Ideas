#include "_genesis.h"
#include "memory.h"

u16 MEM_getFree(void) { return 0; }

u16 MEM_getAllocated(void) { return 0; }

u16 MEM_getLargestFreeBlock(void) { return 0; }

void MEM_free(void *ptr) {}

void*MEM_alloc(u16 size) { return 0; }

void*MEM_allocAt(u32 addr, u16 size) { return 0; }

void MEM_pack(void) {}

void MEM_dump(void) {}

void memset(void *to, u8 value, u16 len) {}

void memsetU16(u16 *to, u16 value, u16 len) {}

void memsetU32(u32 *to, u32 value, u16 len) {}

void memcpy(void *to, const void *from, u16 len) {}

