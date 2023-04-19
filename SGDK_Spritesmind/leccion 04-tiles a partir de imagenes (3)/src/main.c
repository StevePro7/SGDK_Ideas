#include "main.h"

int main()
{
	u16 ind;
	u16 *data1, *data2;
	u16 numTile1, numTile2;

	data1 = data2 = NULL;;
	numTile1 = numTile2 = 0;

#ifdef _CONSOLE
#else
	data1 = block.palette->data;
	data2 = block2.palette->data;
	numTile1 = block.tileset->numTile;
	numTile2 = block2.tileset->numTile;
#endif

	VDP_setPalette( PAL0, data1 );
	VDP_setPalette( PAL1, data2 );

	ind = 1;

	VDP_drawImageEx( BG_A, &block, TILE_ATTR_FULL( PAL0, 0, 0, 0, ind ), 3, 3, 1, CPU );
	ind += numTile1;
	VDP_drawImageEx( BG_B, &block2, TILE_ATTR_FULL( PAL1, 0, 0, 0, ind ), 3, 3, 1, CPU );
	ind += numTile2;

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
