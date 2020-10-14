#include "main.h"

int main()
{
	engine_best_screen_load();
	while( 1 )
	{
		engine_best_screen_udpate();
		VDP_waitVSync();
	}

	return 0;
}