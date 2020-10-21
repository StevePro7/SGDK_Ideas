#include "main.h"

int main()
{
	engine_audio_manager_init();

	//VDP_loadTileData( ( const u32 * ) tile, 1, 1, 0 );
	//VDP_setTileMap( BG_A, TILE_ATTR_FULL( PAL0, 0, 1, 0, 1 ), 6, 5 );
	//VDP_setPaletteColor( PAL2, 0x000E );
	//VDP_setTextPalette( PAL2 );
	VDP_setTextPalette( PAL0 );
	VDP_drawText( "Hello Genie!", 10, 12 );

	//int data = screen_play_screen_init();
	int data = engine_audio_manager_test();
	if (14 == data )
	{
		VDP_setTextPalette( PAL2 );
		VDP_drawText( "Hello Genny World 14", 10, 13 );
	}

	VDP_setTextPalette( PAL0 );
	VDP_drawText( "Hello Genny World AA", 10, 14 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}