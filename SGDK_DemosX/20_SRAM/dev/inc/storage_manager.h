#ifndef _STORAGE_MANAGER_H_
#define _STORAGE_MANAGER_H_

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

unsigned char engine_storage_manager_available();
s8 engine_storage_manager_read();
void engine_storage_manager_write();

#endif//_STORAGE_MANAGER_H_