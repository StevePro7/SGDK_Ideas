#include "main.h"

int main()
{
	u16 data = 1;
	while( 1 )
	{
		data = JOY_readJoypad( 0 );
		engine_font_manager_data( data, 8, 4 );

		engine_input_manager_update();
		if( engine_input_manager_move_buttonB() )
		{
			VDP_drawText( "BUTTON B", 10, 10 );
		}
		else if( engine_input_manager_move_buttonC() )
		{
			VDP_drawText( "BUTTON C", 10, 10 );
		}
		else
		{
			VDP_drawText( "         ", 10, 10 );
		}
		//if( engine_input_manager_hold_down() )
		//{
		//	VDP_drawText( "         ", 10, 10 );
		//}

		VDP_waitVSync();
	}

	return 0;
}

