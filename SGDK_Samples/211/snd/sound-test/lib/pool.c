#include "pool.h"

Pool*POOL_create(u16 size, u16 objectSize) { return 0; }

void POOL_destroy(Pool* pool) {}

void POOL_reset(Pool* pool, bool clear) {}

void*POOL_allocate(Pool* pool) { return 0; }

void POOL_release(Pool* pool, void* object, bool maintainCoherency) {}

u16 POOL_getFree(Pool* pool) { return 0; }

u16 POOL_getNumAllocated(Pool* pool) { return 0; }

void**POOL_getFirst(Pool* pool) { return 0; }

s16 POOL_find(Pool* pool, void* object) { return 0; }

