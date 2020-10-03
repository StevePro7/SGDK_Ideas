#include "main.h"

int main()
{
	u16 *data = NULL;
	int score = screen_play_screen_init();

	// get the palette data of moon
#ifndef _CONSOLE
	if( !score )
	{
		data = moon.palette->data;
	}
	else
	{
		data = logo.palette->data;
	}
#endif

	VDP_setPalette( PAL1, data );

	// draw the moon at (12,12)
	if( !score )
	{
		VDP_drawImageEx( BG_A, &moon, TILE_ATTR_FULL( PAL1, 0, 0, 0, 1 ), 10, 5, 0, CPU );
	}
	else
	{
		VDP_drawImageEx( BG_A, &logo, TILE_ATTR_FULL( PAL1, 0, 0, 0, 1 ), 10, 5, 0, CPU );
	}

	if( !score )
	{
		VDP_drawText( "ONE TEXT", 2, 0 );
	}
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}