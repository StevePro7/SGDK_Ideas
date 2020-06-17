#include "main.h"

int main()
{
	VDP_drawText( "Hello Genny World!", 10, 13 );
	while( 1 )
	{
		//read input
		//move sprite
		//update score
		//draw current screen (logo, start screen, settings, game, gameover, credits...)

		//wait for screen refresh
		VDP_waitVSync();
	}

	return 0;
}