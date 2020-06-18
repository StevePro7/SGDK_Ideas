#include "main.h"

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	if( joy == JOY_1 )
	{
		if( state & BUTTON_START )
		{
			VDP_drawText( "player 1 pressed  START button ", 5, 13 );
		}
		else if( changed & BUTTON_START )
		{
			VDP_drawText( "player 1 released START button", 5, 13 );
		}
	}
}
int main()
{
	VDP_drawText( "player 1 released START button", 5, 13 );

	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}