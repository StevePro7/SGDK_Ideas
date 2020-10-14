#ifndef _TIMER_MANAGER_H_
#define _TIMER_MANAGER_H_

#include "timer_object.h"

// Global variables.
extern struct_timer_object global_timer_object;

void engine_timer_manager_init();
void engine_timer_manager_load( unsigned short isPAL );
void engine_timer_manager_update();
unsigned char engine_timer_manager_getframe();

#endif//_TIMER_MANAGER_H_