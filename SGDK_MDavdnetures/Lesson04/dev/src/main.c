#include "main.h"

int main()
{
	u16 *data = NULL;
	u16 ind = TILE_USERINDEX;

#ifndef _CONSOLE
	data = moon.palette->data;
#endif

	VDP_setPalette( PAL0, data );
	VDP_drawImageEx( BG_A, &moon, TILE_ATTR_FULL( PAL0, 0, 0, 0, ind ), 3, 3, 0, CPU );
	ind += moon.tileset->numTile;

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
