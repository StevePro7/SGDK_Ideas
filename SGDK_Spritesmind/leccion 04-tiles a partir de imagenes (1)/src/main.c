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
	data = moon.palette->data;
	numTile = moon.tileset->numTile;
#endif
	VDP_setPalette( PAL0, data );
	ind = TILE_USERINDEX;

	VDP_drawImageEx( BG_A, &moon, TILE_ATTR_FULL( PAL0, 0, 0, 0, ind ), 3, 3, 0, CPU );
	ind += numTile;
	while(1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
