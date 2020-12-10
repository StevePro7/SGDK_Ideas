#include "main.h"

int main()
{
	unsigned char input;
	VDP_drawText( "BUTTON A : PLAY   music", 5, 1 );
	VDP_drawText( "LEFT     : Pause  music", 5, 2 );
	VDP_drawText( "RIGHT    : Resume music", 5, 3 );

	// init SFX
	SND_setPCM_XGM( SFX_DEAD, sonic_dead_sfx, sizeof( sonic_dead_sfx ) );
	SND_setPCM_XGM( SFX_KILL, sonic_kill_sfx, sizeof( sonic_kill_sfx ) );
	SND_setPCM_XGM( SFX_MIKE, sonic_mike_sfx, sizeof( sonic_mike_sfx ) );
	SND_setPCM_XGM( SFX_OVER, sonic_over_sfx, sizeof( sonic_over_sfx ) );
	SND_setPCM_XGM( SFX_RING, sonic_ring_sfx, sizeof( sonic_ring_sfx ) );
	SND_setPCM_XGM( SFX_STOP, sonic_stop_sfx, sizeof( sonic_stop_sfx ) );

	while( 1 )
	{
		engine_input_manager_update();
		input = engine_input_manager_hold_buttonA();
		if( input )
		{
			VDP_drawText( "PLAY! ", 10, 10 );
			SND_startPlay_XGM( comic_music );
			//SND_startPlay_XGM( sonic_music );
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
					VDP_drawText( "pause ", 10, 10 );
					SND_pausePlay_XGM();
				}
				else
				{
					input = engine_input_manager_hold_right();
					if( input )
					{
						VDP_drawText( "resume", 10, 10 );
						SND_resumePlay_XGM();
					}
				}
			}
		}

		input = engine_input_manager_hold_buttonB();
		if( input )
		{
			//SND_startPlayPCM_XGM( SFX_DEAD, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_KILL, 1, SOUND_PCM_CH2 );
			SND_startPlayPCM_XGM( SFX_MIKE, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_OVER, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_RING, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_STOP, 1, SOUND_PCM_CH2 );
		}
		input = engine_input_manager_hold_buttonC();
		if( input )
		{
			//SND_startPlayPCM_XGM( SFX_DEAD, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_KILL, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_MIKE, 1, SOUND_PCM_CH2 );
			SND_startPlayPCM_XGM( SFX_OVER, 1, SOUND_PCM_CH3 );
			//SND_startPlayPCM_XGM( SFX_RING, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_STOP, 1, SOUND_PCM_CH2 );
		}

		VDP_waitVSync();
	}

	return 0;
}

