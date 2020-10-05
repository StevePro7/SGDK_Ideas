#include "hack_manager.h"

// Global variable.
struct_hack_object global_hack_object;

#define PEEK( addr)			(* ( unsigned char *)( addr ) )
#define POKE( addr, data )	(* ( unsigned char *)( addr ) = ( data ) )

#define HACKER_START		0x0052

void engine_hack_manager_init()
{
}

void engine_hack_manager_load()
{
}

void engine_hack_manager_invert()
{
}