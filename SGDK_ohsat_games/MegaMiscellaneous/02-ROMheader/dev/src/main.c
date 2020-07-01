#include "main.h"

int main()
{
	VDP_drawText( "Custom ROM Header", 10, 10 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}
