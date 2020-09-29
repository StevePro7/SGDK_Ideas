#include "main.h"

int main()
{
	VDP_drawText( "Hello Genny World AA", 10, 13 );
	VDP_drawText( "Hello Genny World DD", 10, 14 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}