#include "main.h"

int main()
{
	VDP_drawText( "Miscellaneous 03", 10, 10 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

