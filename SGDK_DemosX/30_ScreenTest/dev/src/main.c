#include "main.h"

int main()
{
	unsigned char open_screen_type;

	open_screen_type = screen_type_splash;

	engine_font_manager_data( open_screen_type, 10, 6 );
	engine_font_manager_text( "STEVEPRO STUDIOS", 10, 5 );
	engine_font_manager_text( "X", 10, 7 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

