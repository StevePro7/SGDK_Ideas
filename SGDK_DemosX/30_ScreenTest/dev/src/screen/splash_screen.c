#include "splash_screen.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "input_manager.h"

void screen_splash_screen_load()
{
	engine_font_manager_clear( 0, 12, 40 );
	engine_font_manager_text( "SPLASH", 10, 10 );
}

void screen_splash_screen_update( unsigned char *screen_type )
{
	unsigned char test = engine_input_manager_hold_right();
	if( test )
	{
		*screen_type = screen_type_intro;
		return;
	}

	*screen_type = screen_type_splash;
}