#include "main.h"

int main()
{
	u16 *data = NULL;

#ifndef _CONSOLE
	data = splash.palette->data;
#endif

	VDP_setPalette( PAL1, data );
	VDP_drawImageEx( BG_A, &splash, TILE_ATTR_FULL( PAL1, 0, 0, 0, 1 ), 4, 2, 0, CPU );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
