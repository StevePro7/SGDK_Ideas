#include "main.h"

static void handleInput();

int main()
{
	u16 ind;
	u16 *dataB, *dataA;
	u16 numTileB, numTileA;

	dataB = dataA = NULL;;
	numTileB = numTileA = 0;

	u16 paleta_completa[ 64 ];

#ifdef _CONSOLE
#else
	dataB = bgb_image.palette->data;
	dataA = bga_image.palette->data;
	numTileB = bgb_image.tileset->numTile;
	numTileA = bga_image.tileset->numTile;
#endif

	ind = 1;

	SYS_disableInts();

	VDP_setScreenWidth320();
	VDP_setPaletteColors( 0, ( u16* ) paleta_completa, 64 );

	VDP_drawImageEx( BG_B, &bgb_image, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTileB;
	VDP_drawImageEx( BG_A, &bga_image, TILE_ATTR_FULL( PAL1, FALSE, FALSE, FALSE, ind ), 20, 0, FALSE, TRUE );
	ind += numTileA;

	SYS_enableInts();

	memcpy( &paleta_completa[ 0 ], dataB, 16 * 2 );
	memcpy( &paleta_completa[ 16 ], dataA, 16 * 2 );

	VDP_fadeIn( 0, 63, paleta_completa, 100, FALSE );

	while( 1 )
	{
		handleInput();
		VDP_waitVSync();
	}

	return 0;
}

static void handleInput()
{
	//variable donde se guarda la entrada del mando
	u16 value = JOY_readJoypad( JOY_1 );

	//si pulsamos izquierda...
	if( value & BUTTON_LEFT )    VDP_drawText( "IZQUIERDA", 8, 10 );

	//si pulsamos derecha...
	if( value & BUTTON_RIGHT )   VDP_drawText( "DERECHA", 20, 10 );

	//si pulsamos izquierda...
	if( value & BUTTON_UP )      VDP_drawText( "ARRIBA", 16, 8 );

	//si pulsamos derecha...
	if( value & BUTTON_DOWN )    VDP_drawText( "ABAJO", 16, 12 );

	//si pulsamos A...
	if( value & BUTTON_A )       VDP_drawText( "BOTON A", 6, 18 );

	//si pulsamos B...
	if( value & BUTTON_B )       VDP_drawText( "BOTON B", 14, 18 );

	//si pulsamos C...
	if( value & BUTTON_C )       VDP_drawText( "BOTON C", 22, 18 );

	//si pulsamos X...
	if( value & BUTTON_X )       VDP_drawText( "BOTON X", 6, 20 );

	//si pulsamos Y...
	if( value & BUTTON_Y )       VDP_drawText( "BOTON Y", 14, 20 );

	//si pulsamos Z...
	if( value & BUTTON_Z )       VDP_drawText( "BOTON Z", 22, 20 );

	//si pulsamos START...
	if( value & BUTTON_START )   VDP_drawText( "START", 10, 16 );

	//si pulsamos MODE...
	if( value & BUTTON_MODE )    VDP_drawText( "MODE", 20, 16 );

	//si NO pulsamos nada, borra todo del título hacia abajo (VDP_clearTextArea() trabaja en tiles)
	if( ( !( value & BUTTON_UP ) ) && ( !( value & BUTTON_DOWN ) ) && ( !( value & BUTTON_LEFT ) ) &&
		( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_A ) ) && ( !( value & BUTTON_B ) ) &&
		( !( value & BUTTON_C ) ) && ( !( value & BUTTON_X ) ) && ( !( value & BUTTON_Y ) ) &&
		( !( value & BUTTON_Z ) ) && ( !( value & BUTTON_MODE ) ) && ( !( value & BUTTON_START ) ) )
		VDP_clearTextArea( 0, 7, 40, 28 );

}
