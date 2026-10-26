#ifndef SAVE_H
#define SAVE_H
#include "wl_types.h"
#define SAVE_SLOTS      3
#define SAVE_NAMELEN    20
boolean Save_Used(s16 slot);
void Save_Name(s16 slot, char *out);       /* out: SAVE_NAMELEN bytes */
boolean Save_Write(s16 slot, const char *name);
boolean Save_Read(s16 slot);
void Scores_Load(void);
void Scores_Store(void);
#endif
