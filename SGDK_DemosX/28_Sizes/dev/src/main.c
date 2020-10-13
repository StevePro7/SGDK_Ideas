#include "main.h"

int main()
{
	engine_font_manager_text("Hello tests", 10, 13 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}