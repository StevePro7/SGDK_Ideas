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
	u8 data = 0;
	engine_hack_manager_init();
	engine_hack_manager_load();

	data = engine_hack_manager_data();
	updateScoreDisplay( data, 10, 10 );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

