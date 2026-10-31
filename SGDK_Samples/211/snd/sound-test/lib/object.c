#include "object.h"

Pool*OBJ_createObjectPool(u16 size, u16 objectSize) { return 0; }

Object*OBJ_create(Pool* pool) { return 0; }

void OBJ_release(Pool* pool, Object* object, bool maintainCoherency) {}

void OBJ_updateAll(Pool* pool) {}

void OBJ_setInitMethod(Object* object, ObjectCallback* initMethod) {}

void OBJ_setUpdateMethod(Object* object, ObjectCallback* updateMethod) {}

void OBJ_setEndMethod(Object* object, ObjectCallback* endMethod) {}

