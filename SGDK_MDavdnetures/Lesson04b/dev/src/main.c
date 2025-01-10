#include "main.h"

int main()
{
	u16 *data = NULL;
	u16 ind = 1;

#ifndef _CONSOLE
	data = my64tiles.palette->data;
#endif
	ind = 1;

	VDP_setPalette( PAL0, data );
	ind = 1;

	VDP_drawImageEx( BG_B, &my64tiles, TILE_ATTR_FULL( PAL0, 0, 0, 0, ind ), 3, 3, 0, CPU );
	ind += my64tiles.tileset->numTile;

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
