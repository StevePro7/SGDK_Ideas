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
	s8 data;
	s8 data2;

	//engine_storage_manager_write();
	data = engine_storage_manager_read();
	data2 = engine_storage_manager_read2();

	//data = 0;
	//data2 = 1;
	updateScoreDisplay( data, 2, 1 );
	updateScoreDisplay( data2, 2, 2 );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

