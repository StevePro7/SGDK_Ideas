#include "main.h"

#define TILE1	1


int main()
{
	u16 *data = NULL;

	// get the palette data of moon
#ifndef _CONSOLE
	data = moon.palette->data;
#endif

	VDP_setPalette( PAL1, data );

	// draw the moon at (12,12)
	VDP_drawImageEx( BG_A, &moon, TILE_ATTR_FULL( PAL1, 0, 0, 0, 1 ), 10, 5, 0, CPU );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

