#include "main.h"

int main()
{
	VDP_drawText( "ROM header", 10, 10 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

