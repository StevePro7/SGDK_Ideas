#include "main.h"

u16 color_gray = -1;
u16 color_blue = -1;
u16 color_default = -1;

void swapToColor( u16 Col )
{
	VDP_setPaletteColor( 18, Col );
}

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	if( joy != JOY_1 )
	{
		return;
	}

	if( state & BUTTON_A & changed )
	{
		swapToColor( color_gray );
	}
	else if( state & BUTTON_B & changed )
	{
		swapToColor( color_blue );
	}
	else if( state & BUTTON_C & changed )
	{
		swapToColor( color_default );
	}
}

int main()
{
	u16 *data = NULL;

	//Input
	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

	/*Grab the palette data from the runner sprite and stick it in PAL1*/
#ifndef _CONSOLE
	data = runner.palette->data;
#endif
	VDP_setPalette( PAL1, data );

	/*Start the sprite engine and add the player sprites*/
	SPR_init( 0, 0, 0 );
	for( int i = 0; i < 10; i++ )
	{
		SPR_addSprite( &runner, 64 + ( i * 16 ), 64, TILE_ATTR( PAL1, 0, FALSE, FALSE ) );
	}

	SPR_update();

	//Set up colors
	color_gray = RGB24_TO_VDPCOLOR( 0x808080 );
	color_blue = RGB24_TO_VDPCOLOR( 0x0000ff );
	color_default = VDP_getPaletteColor( 18 );

	while( 1 )
	{
		SPR_update();
		VDP_waitVSync();
	}

	return 0;
}

