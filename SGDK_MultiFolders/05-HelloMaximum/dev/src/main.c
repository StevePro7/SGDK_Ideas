#include "main.h"

int main()
{
	engine_audio_manager_init();

	//int data = screen_play_screen_init();
	int data = engine_audio_manager_test();
	if (14 == data )
	{
		VDP_drawText( "Hello Genny World 14", 10, 14 );
	}

	VDP_drawText( "Hello Genny World AA", 10, 13 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}