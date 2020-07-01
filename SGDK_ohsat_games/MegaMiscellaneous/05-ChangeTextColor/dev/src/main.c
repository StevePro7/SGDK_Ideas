#include "main.h"

void drawText()
{
	VDP_drawText( "Hello World", 8, 8 );
}

void joyHandlerMenu( u16 joy, u16 changed, u16 state )
{
	if( joy != JOY_1 )
	{
		return;
	}

	if( state & BUTTON_START & changed )
	{
		VDP_setPaletteColor( 15, RGB24_TO_VDPCOLOR( 0xff0000 ) );
		VDP_drawText( "Hello World", 8, 8 );
	}
}

int main()
{
	JOY_init();
	JOY_setEventHandler( joyHandlerMenu );

	drawText();
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

