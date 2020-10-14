#include "best_screen.h"
#include "font_manager.h"

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

void engine_best_screen_load()
{
	unsigned short data1 = 0;
	unsigned short data2 = 0;

	engine_font_manager_text( "Hello sizes", 10, 13 );

	data1 = SYS_isNTSC();
	data2 = SYS_isPAL();
	engine_font_manager_data( data1, 10, 14 );
	engine_font_manager_data( data2, 10, 15 );
	engine_font_manager_text( "NTSC", 8, 14 );
	engine_font_manager_text( "PAL ", 8, 15 );

	engine_font_manager_data( screenWidth, 15, 17 );
	engine_font_manager_data( screenHeight, 15, 18);
	engine_font_manager_text( "WIDE", 8, 17 );
	engine_font_manager_text( "HIGH ", 8, 18 );

}

void engine_best_screen_udpate()
{
}
