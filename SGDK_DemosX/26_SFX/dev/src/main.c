#include "main.h"

int main()
{
	unsigned char input;
	VDP_drawText( "MUSIC", 5, 5 );

	// init SFX
	SND_setPCM_XGM( SFX_STOP, sonic_stop_sfx, sizeof( sonic_stop_sfx ) );

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

		input = engine_input_manager_hold_buttonA();
		if( input )
		{
			SND_startPlayPCM_XGM( SFX_STOP, 1, SOUND_PCM_CH2 );
		}

		VDP_waitVSync();
	}

	return 0;
}

