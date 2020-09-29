#include "main.h"

int main()
{
	int data = engine_data_manager_test();
	//int test = test_manager_data();
	if (17 == data )
	{
		VDP_drawText( "Hello Genny World 17", 10, 14 );
	}

	VDP_drawText( "Hello Genny World AA", 10, 13 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}