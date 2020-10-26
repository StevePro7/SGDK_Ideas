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
	s8 data;
	s8 data2;

	VDP_drawText( "Press A to read!", 10, 5 );
	VDP_drawText( "Press B to write", 10, 6 );
	VDP_drawText( "Press C to erase", 10, 7 );

	data = engine_storage_manager_read();
	data2 = engine_storage_manager_read2();
	updateScoreDisplay( data, 2, 1 );
	updateScoreDisplay( data2, 2, 2 );
	while( 1 )
	{
		engine_input_manager_update();
		input = engine_input_manager_hold_buttonA();
		if( input )
		{
			VDP_drawText( "Reading START", 10, 11 );
			engine_storage_manager_read();
			VDP_drawText( "Reading -END-", 10, 14 );

			data = engine_storage_manager_read();
			data2 = engine_storage_manager_read2();
			updateScoreDisplay( data, 2, 1 );
			updateScoreDisplay( data2, 2, 2 );

		}

		input = engine_input_manager_hold_buttonB();
		if( input )
		{
			VDP_drawText( "Writing START", 10, 11 );
			engine_storage_manager_write();
			VDP_drawText( "Writing -END-", 10, 14 );
		}

		input = engine_input_manager_hold_buttonC();
		if( input )
		{
			VDP_drawText( "Clearing START", 10, 11 );
			engine_storage_manager_erase();
			VDP_drawText( "Clearing -END-", 10, 14 );

			data = engine_storage_manager_read();
			data2 = engine_storage_manager_read2();
			updateScoreDisplay( data, 2, 1 );
			updateScoreDisplay( data2, 2, 2 );

		}

		VDP_waitVSync();
	}

	return 0;
}

