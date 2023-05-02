#include "main.h"

int main()
{
	u16 ind, contador;
	u16 *data = NULL;
	u16 numTile = 0;
	
#ifndef _CONSOLE
	data = bga_image.palette->data;
	numTile = bga_image.tileset->numTile;
#endif //

	SYS_disableInts();

	VDP_setScreenWidth320();
	VDP_setPalette( PAL0, data );

	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_A, &bga_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile;
	
	SYS_enableInts();
	contador = 0;
	while( 1 )
	{
		contador++;

		if( contador > 60 * 1 )     VDP_setPaletteColor( 4, RGB24_TO_VDPCOLOR( 0xFF6600 ) );
		if( contador > 60 * 2 )     VDP_setPaletteColor( 4, RGB24_TO_VDPCOLOR( 0xCC5200 ) );
		if( contador > 60 * 3 )     VDP_setPaletteColor( 4, RGB24_TO_VDPCOLOR( 0x993D00 ) );
		if( contador > 60 * 4 )     VDP_setPaletteColor( 4, RGB24_TO_VDPCOLOR( 0x662900 ) );
		if( contador > 60 * 5 )     VDP_setPaletteColor( 4, RGB24_TO_VDPCOLOR( 0x000000 ) );

		//cambio de castillo (rojo->rojo oscuro)
		if( contador > 60 * 3 )     VDP_setPaletteColor( 2, RGB24_TO_VDPCOLOR( 0x802000 ) );
		if( contador > 60 * 4 )     VDP_setPaletteColor( 12, RGB24_TO_VDPCOLOR( 0x661A00 ) );

		//cambio del cesped (verde->marr�n)
		if( contador > 60 * 1 )     VDP_setPaletteColor( 8, RGB24_TO_VDPCOLOR( 0x999900 ) );
		if( contador > 60 * 2 )     VDP_setPaletteColor( 1, RGB24_TO_VDPCOLOR( 0x997300 ) );

		VDP_waitVSync();
	}

	return 0;
}
