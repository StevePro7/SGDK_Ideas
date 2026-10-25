#include "_genesis.h"
#include "string.h"

u16 strlen(const char *str) { return 0; }

u16 strnlen(const char *str, u16 maxlen) { return 0; }

s16 strcmp(const char *str1, const char *str2) { return 0; }

char*strcpy(char *dest, const char *src) { return 0; }

char*strncpy(char *dest, const char *src, u16 len) { return 0; }

char*strcat(char *dest, const char *src) { return 0; }

int vsprintf(char *buffer, const char *fmt, va_list args) { return 0; }

int sprintf(char *buffer, const char *fmt, ...) { return 0; }

char*strclr(char *str) { return 0; }

char *strreplacechar(char *str, char oldc, char newc) { return 0; }

u16 intToStr(s32 value, char *str, u16 minsize) { return 0; }

u16 uintToStr(u32 value, char *str, u16 minsize) { return 0; }

u16 intToHex(u32 value, char *str, u16 minsize) { return 0; }

void fix16ToStr(fix16 value, char *str, u16 numdec) {}

void fix32ToStr(fix32 value, char *str, u16 numdec) {}

void fastFix16ToStr(fastfix16 value, char *str, u16 numdec) {}

void fastFix32ToStr(fastfix32 value, char *str, u16 numdec) {}

void F16_toStr(fix16 value, char *str, u16 numdec) {}

void F32_toStr(fix32 value, char *str, u16 numdec) {}

void FF16_toStr(fastfix16 value, char *str, u16 numdec) {}

void FF32_toStr(fastfix32 value, char *str, u16 numdec) {}

