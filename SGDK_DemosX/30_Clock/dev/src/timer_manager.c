#include "timer_manager.h"
#include "font_manager.h"

// Global variables.
struct_timer_object global_timer_object;

void engine_timer_manager_init()
{
	struct_timer_object *to = &global_timer_object;
	to->frame = 0;
	to->ticks = 0;

	engine_font_manager_data( to->ticks, 9, 9 );
}

void engine_timer_manager_load( unsigned short isPAL )
{
	struct_timer_object *to = &global_timer_object;
	unsigned char fps[ 2 ] = { 50, 60 };
	
	to->count = fps[ isPAL ];
}

void engine_timer_manager_update()
{
	struct_timer_object *to = &global_timer_object;
	to->frame++;

	if( to->frame >= to->count )
	{
		to->frame = 0;
		to->ticks++;

		engine_font_manager_data( to->ticks, 9, 9 );
	}
}

unsigned char engine_timer_manager_getframe()
{
	struct_timer_object *to = &global_timer_object;
	return to->count;
	//return to->frame;
}