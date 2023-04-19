#include "main.h"

int main()
{
	u16 ind;
	u16* data;
	u16 numTile;

	data = NULL;
	numTile = 0;

#ifdef _CONSOLE
#else
	data = my64tiles.palette->data;
	numTile = my64tiles.tileset->numTile;
#endif

	VDP_setPalette( PAL0, data );
	ind = 1;

	VDP_drawImageEx( BG_B, &my64tiles, TILE_ATTR_FULL( PAL0, 0, 0, 0, ind ), 3, 3, 0, CPU );
	ind += numTile;

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
