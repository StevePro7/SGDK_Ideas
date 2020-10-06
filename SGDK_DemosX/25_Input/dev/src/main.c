#include "main.h"




int main()
{
	u16 data = 1;
	engine_hack_manager_init();
	engine_hack_manager_load();

	//engine_font_manager_data( data, 8, 4 );
	//engine_font_manager_data( 10, 8, 5 );
	//engine_font_manager_data( 100, 8, 8 );

	while( 1 )
	{
		data = JOY_readJoypad( 0 );
		engine_font_manager_data( data, 8, 4 );
		VDP_waitVSync();
	}

	return 0;
}

