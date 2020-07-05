#include "main.h"

char str_score[ 3 ] = "0";

int main()
{
	unsigned char test = engine_storage_manager_available();
	if( test )
	{
		VDP_drawText( "non zero", 10, 10 );
	}
	else
	{
		VDP_drawText( "ZERO", 10, 10 );
	}

	engine_storage_manager_write();
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

