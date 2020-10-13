#include "main.h"

int main()
{
	u16 data1 = 0;
	u16 data2 = 0;
	engine_font_manager_text("Hello tests", 10, 13 );

	data1 = SYS_isNTSC();
	data2 = SYS_isPAL();
	engine_font_manager_data( data1, 10, 14 );
	engine_font_manager_data( data2, 10, 15 );

	engine_font_manager_text( "NTSC", 8, 14 );
	engine_font_manager_text( "PAL ", 8, 15 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}