#include "main.h"

int main()
{
	unsigned char input;
	VDP_drawText( "MUSIC", 5, 5 );

	while( 1 )
	{
		engine_input_manager_update();
		input = engine_input_manager_hold_up();
		if( input )
		{
			VDP_drawText( "UP", 10, 10 );
			SND_startPlay_XGM( sonic_music );
		}
		else
		{
			input = engine_input_manager_hold_down();
			if( input )
			{
				SND_stopPlay_XGM();
			}
			else
			{
				input = engine_input_manager_hold_left();
				if( input )
				{
					SND_pausePlay_XGM();
				}
				else
				{
					input = engine_input_manager_hold_right();
					if( input )
					{
						SND_resumePlay_XGM();
					}
				}
			}
		}
		VDP_waitVSync();
	}

	return 0;
}

