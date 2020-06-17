#include "main.h"

#define TILE1	1

//const is used to keep tile in ROM, not in RAM
const u32 tile[ 8 ] =
{
	0x00111100,
	0x01144110,
	0x11244211,
	0x11244211,
	0x11222211,
	0x11222211,
	0x01122110,
	0x00111100
};

int main()
{
	//This will fill the background with this tile
	//VDP_loadTileData( (const u32 *)tile, 0, 1, 0);

	//load the tile in VRAM (check it using GensKMod CPU>Debug>Genesis>VDP)
	VDP_loadTileData( ( const u32 * ) tile, TILE1, 1, 0 );

	//draw this tile at (5,5) using PAL0
	VDP_setTileMapXY( BG_A, TILE1, 5, 5 );

	//draw this tile flipped on B plane at (6,5) using PAL2 (default : green gradient)
	//PAL2 = green pal
	// 0 = low priority
	// 1 = vflip
	// 0 = no hflip
	// 1 = tile 1
	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL2, 0, 1, 0, TILE1 ), 6, 5 );

	//tile at same position with 2 pal...which one is in front ? the one with field priority 1
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL1, 1, 0, 0, TILE1 ), 7, 7 );
	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL2, 0, 0, 0, TILE1 ), 7, 7 );
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL1, 0, 0, 0, TILE1 ), 8, 7 );
	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL2, 1, 0, 0, TILE1 ), 8, 7 );

	//same priority, BG_A first
	//write order doesn't define the priority
	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL2, 1, 0, 0, TILE1 ), 9, 7 );
	VDP_setTileMapXY( BG_A, TILE_ATTR_FULL( PAL1, 1, 0, 0, TILE1 ), 9, 7 );
	VDP_setTileMapXY( BG_B, TILE_ATTR_FULL( PAL2, 1, 0, 0, TILE1 ), 9, 7 );

	//fill a square filled of tile 1 in blue => 1 tile in memory, 64 on screen
	VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL3, 0, 0, 0, TILE1 ), 12, 12, 8, 8 );

	while( 1 )
	{
		//psycho fx! (pause/continue with Esc key on Gens KMod to see it step by step)
		VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL0, 0, 0, 0, TILE1 ), 12, 1, 4, 4 );
		VDP_waitVSync(); //50Hz is too fast ;)
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL1, 0, 1, 0, TILE1 ), 12, 1, 4, 4 );
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL2, 0, 0, 0, TILE1 ), 12, 1, 4, 4 );
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_fillTileMapRect( BG_B, TILE_ATTR_FULL( PAL3, 0, 1, 0, TILE1 ), 12, 1, 4, 4 );
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
		VDP_waitVSync();
	}

	return 0;
}
