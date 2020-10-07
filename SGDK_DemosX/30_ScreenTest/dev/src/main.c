#include "main.h"

int main()
{
	unsigned char open_screen_type;

	open_screen_type = screen_type_splash;
	engine_font_manager_data( 2048, 10, 6 );
	engine_font_manager_text( "STEVEPRO STUDIOS", 10, 5 );
	engine_font_manager_text( "X", 10, 7 );

	engine_screen_manager_init( open_screen_type );
	while( 1 )
	{
		engine_input_manager_update();
		VDP_waitVSync();
	}

	return 0;
}

