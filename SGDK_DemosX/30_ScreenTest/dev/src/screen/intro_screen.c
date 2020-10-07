#include "intro_screen.h"
#include "enum_manager.h"
#include "font_manager.h"
#include "input_manager.h"

static unsigned char pos;

void screen_intro_screen_load()
{
	engine_font_manager_clear( pos, 12, 40 );
	engine_font_manager_text( "INTRO ", 10, 10 );
	pos = 0;
}

void screen_intro_screen_update( unsigned char *screen_type )
{
	unsigned char input = engine_input_manager_move_up();
	if( input )
	{
		if( pos < 40 )
		{
			engine_font_manager_text( "X", pos, 12 );
			pos++;
		}
	}
	else
	{
		input = engine_input_manager_hold_left();
		if( input )
		{
			*screen_type = screen_type_splash;
			return;
		}
	}

	*screen_type = screen_type_intro;
}