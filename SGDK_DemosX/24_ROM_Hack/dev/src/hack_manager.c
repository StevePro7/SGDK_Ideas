#include "hack_manager.h"

// Global variable.
struct_hack_object global_hack_object;

#define PEEK( addr)			(* ( unsigned char *)( addr ) )
#define POKE( addr, data )	(* ( unsigned char *)( addr ) = ( data ) )

#define HACKER_START		0x0053

void engine_hack_manager_init()
{
	struct_hack_object *ho = &global_hack_object;
	ho->hack_object_byte_data = 4;
}

void engine_hack_manager_load()
{
	struct_hack_object *ho = &global_hack_object;

#ifndef _CONSOLE

	ho->hack_object_byte_data = PEEK( HACKER_START + 0 );			// 0x0052

#endif
}

unsigned char engine_hack_manager_data()
{
	struct_hack_object *ho = &global_hack_object;
	return ho->hack_object_byte_data;
}