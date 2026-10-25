#include "_genesis.h"
#include "console.h"

int CON_sprintf(char* buf, const char *fmt, ...) { return 0; }

int CON_snprintf(char* buf, int count, const char *fmt, ...) { return 0; }

void CON_setVsprintf(vsprintf_t vsprintf_func) {}

void CON_setVsnprintf(vsnprintf_t vsnprintf_func) {}

void CON_setConsoleSize(u16 left, u16 top, u16 width, u16 height) {}

void CON_setLineBufferSize(u16 size) {}

void CON_setTransferMethod(TransferMethod tm) {}

void CON_reset() {}

void CON_systemResetOnNextWrite() {}

void CON_clear() {}

void CON_setCursorPosition(u16 x, u16 y) {}

V2u16 CON_getCursorPosition() { V2u16 r = {0, 0}; return r; }

int CON_write(const char *fmt, ...) { return 0; }

