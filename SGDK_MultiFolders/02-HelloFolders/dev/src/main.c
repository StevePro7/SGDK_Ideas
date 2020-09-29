#include "main.h"

int main()
{
	int data = engine_data_manager_test();
	if (19 == data )
	{
		VDP_drawText( "Hello Genny World 19", 10, 14 );
	}

	VDP_drawText( "Hello Genny World AA", 10, 13 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}