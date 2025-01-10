#include "main.h"

int main()
{
	u16 *data = NULL;
	u16 *data2 = NULL;
	u16 ind = 1;

#ifndef _CONSOLE
	data = block.palette->data;
	data2 = block2.palette->data;
#endif

	VDP_setPalette( PAL0, data );
	VDP_setPalette( PAL1, data2 );

	VDP_drawImageEx( BG_A, &block, TILE_ATTR_FULL( PAL0, 0, 0, 0, ind ), 3, 3, 1, CPU );
	ind += block.tileset->numTile;
	VDP_drawImageEx( BG_B, &block2, TILE_ATTR_FULL( PAL1, 0, 0, 0, ind ), 15, 15, 1, CPU );
	ind += block2.tileset->numTile;

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
