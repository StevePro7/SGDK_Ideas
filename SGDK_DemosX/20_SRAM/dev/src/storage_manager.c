#include "storage_manager.h"

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

unsigned char engine_storage_manager_available()
{
	return 1;
}

void engine_storage_manager_read()
{
}

void engine_storage_manager_write()
{
	SRAM_enable();
	VDP_drawText( "write", 10, 12 );
	SRAM_disable();
}

void engine_storage_manager_erase()
{
	SRAM_enable();
	VDP_drawText( "read", 10, 12 );
	SRAM_disable();
}