#include "storage_manager.h"

s8 engine_storage_manager_read()
{
	s8 data;
	u32 sRamOffSet = 0x0000;
	SYS_disableInts();
	SRAM_enable();
	VDP_drawText( "read START", 10, 16 );
	data = SRAM_readByte( sRamOffSet );
	VDP_drawText( "read -END-", 10, 17 );
	SRAM_disable();
	SYS_enableInts();
	return data;
}

void engine_storage_manager_write()
{
	u32 sRamOffSet = 0x0000;
	SYS_disableInts();
	SRAM_enable();
	VDP_drawText( "write START", 10, 12 );
	SRAM_writeByte( sRamOffSet, 7 );
	VDP_drawText( "write -END-", 10, 13 );
	SRAM_disable();
	SYS_enableInts();
}