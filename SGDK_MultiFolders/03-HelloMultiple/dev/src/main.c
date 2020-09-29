#include "main.h"

int main()
{
	//int data = engine_data_manager_test();
	int play = screen_play_screen_init();
	if (21 == play )
	{
		VDP_drawText( "Hello Genny World 21", 10, 14 );
	}

	VDP_drawText( "Hello Genny World AA", 10, 13 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}