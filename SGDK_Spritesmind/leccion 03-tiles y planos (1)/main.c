#include "main.h"

#define MI_TILE 1

const u32 tile[ 8 ] =
{
	0x44444421,
	0x44442211,
	0x44422110,
	0x44221100,
	0x42211000,
	0x42110000,
	0x21100000,
	0x11000000
};

int main()
{
	VDP_loadTileData( ( const u32 * ) tile, MI_TILE, 1, 0 );

	VDP_setTileMapXY( BG_A, MI_TILE, 1, 5 );

	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL2, 0, 0, 0, MI_TILE ), 3, 5 );

	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL0, 0, 0, 0, MI_TILE ), 5, 5 );
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL1, 0, 0, 0, MI_TILE ), 5, 5 );

	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL0, 1, 0, 0, MI_TILE ), 7, 5 );
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL1, 0, 0, 0, MI_TILE ), 7, 5 );

	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL0, 1, 0, 1, MI_TILE ), 3, 8 );
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL0, 1, 1, 0, MI_TILE ), 5, 8 );
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL0, 1, 1, 1, MI_TILE ), 7, 8 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
