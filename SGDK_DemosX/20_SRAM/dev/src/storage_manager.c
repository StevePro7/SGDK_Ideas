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

s8 engine_storage_manager_read2()
{
	s8 data2;
	u32 sRamOffSet = 0x0000;
	SYS_disableInts();
	SRAM_enable();
	VDP_drawText( "read2 START", 10, 18 );
	sRamOffSet++;
	data2 = SRAM_readByte( sRamOffSet );
	VDP_drawText( "read2 -END-", 10, 19 );
	SRAM_disable();
	SYS_enableInts();
	return data2;
}

void engine_storage_manager_write()
{
	u32 sRamOffSet = 0x0000;
	SYS_disableInts();
	SRAM_enable();
	VDP_drawText( "write START", 10, 12 );
	SRAM_writeByte( sRamOffSet, 2 );
	sRamOffSet++;
	SRAM_writeByte( sRamOffSet, 5 );
	VDP_drawText( "write -END-", 10, 13 );
	SRAM_disable();
	SYS_enableInts();
}