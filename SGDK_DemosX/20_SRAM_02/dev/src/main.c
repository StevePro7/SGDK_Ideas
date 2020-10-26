#include "main.h"

// http://gendev.spritesmind.net/forum/viewtopic.php?t=3093

char str_score[ 3 ] = "0";

void updateScoreDisplay( u16 value, u16 x, u16 y )
{
	//sprintf( str_score, "%d", score );
	sprintf( str_score, "%d", value );
	VDP_clearText( x, y, 3 );
	VDP_drawText( str_score, x, y );
}

int main()
{
	unsigned char input;

	//engine_storage_manager_write();

	VDP_drawText( "Press A to write", 10, 10 );
	while( 1 )
	{
		engine_input_manager_update();
		input = engine_input_manager_hold_buttonA();
		if( input )
		{
			VDP_drawText( "Writing START", 10, 12 );
			engine_storage_manager_write();
			VDP_drawText( "Writing -ENJ-", 10, 14 );
		}

		VDP_waitVSync();
	}

	return 0;
}

