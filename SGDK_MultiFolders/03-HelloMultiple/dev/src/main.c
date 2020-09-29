#include "main.h"

int main()
{
	int play = screen_play_screen_init();
	if (22 == play )
	{
		VDP_drawText( "Hello Genny World 22", 10, 14 );
	}

	VDP_drawText( "Hello Genny World AA", 10, 13 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}