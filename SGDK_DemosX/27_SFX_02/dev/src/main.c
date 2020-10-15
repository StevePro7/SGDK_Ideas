#include "main.h"

int main()
{
	unsigned char input;
	const u8 *audio;
	u8 index;

	VDP_drawText( "START  : TEST", 5, 1 );
	VDP_drawText( "STOP   : DOWN", 5, 2 );
	VDP_drawText( "PAUSE  : LEFT", 5, 3 );
	VDP_drawText( "RESUME : RGHT", 5, 4 );

	// init SFX
	index = 0;
	//audio = *myaudio[ index ];
	//audio = sonic_kill_sfx;
	//audio = sonic_dead_sfx;
	audio = myaudio[ index ];
	//audio = sonic_jump_sfx;
	SND_setPCM_XGM( SFX_DEAD, audio, sizeof( audio ) );
	//SND_setPCM_XGM( SFX_DEAD, sonic_dead_sfx, sizeof( sonic_dead_sfx ) );
	//SND_setPCM_XGM( SFX_KILL, sonic_kill_sfx, sizeof( sonic_kill_sfx ) );
	//SND_setPCM_XGM( SFX_MIKE, sonic_mike_sfx, sizeof( sonic_mike_sfx ) );
	//SND_setPCM_XGM( SFX_OVER, sonic_over_sfx, sizeof( sonic_over_sfx ) );
	//SND_setPCM_XGM( SFX_RING, sonic_ring_sfx, sizeof( sonic_ring_sfx ) );
	//SND_setPCM_XGM( SFX_STOP, sonic_stop_sfx, sizeof( sonic_stop_sfx ) );

	//VDP_drawText( "PRESSED: TEST", 5, 10 );
	while( 1 )
	{
		engine_input_manager_update();

		input = engine_input_manager_hold_buttonB();
		if( input )
		{
			VDP_drawText( "PRESSED: OKKK", 5, 10 );

			SND_startPlayPCM_XGM( SFX_DEAD, 1, SOUND_PCM_CH2 );
			//SND_startPlayPCM_XGM( SFX_KILL, 1, SOUND_PCM_CH2 );
		//	SND_startPlayPCM_XGM( SFX_MIKE, 1, SOUND_PCM_CH2 );
		//	//SND_startPlayPCM_XGM( SFX_OVER, 1, SOUND_PCM_CH2 );
		//	//SND_startPlayPCM_XGM( SFX_RING, 1, SOUND_PCM_CH2 );
		//	//SND_startPlayPCM_XGM( SFX_STOP, 1, SOUND_PCM_CH2 );
		}
		//input = engine_input_manager_hold_buttonB();
		//if( input )
		//{
		//	//SND_startPlayPCM_XGM( SFX_DEAD, 1, SOUND_PCM_CH2 );
		//	//SND_startPlayPCM_XGM( SFX_KILL, 1, SOUND_PCM_CH2 );
		//	//SND_startPlayPCM_XGM( SFX_MIKE, 1, SOUND_PCM_CH2 );
		//	SND_startPlayPCM_XGM( SFX_OVER, 1, SOUND_PCM_CH3 );
		//	//SND_startPlayPCM_XGM( SFX_RING, 1, SOUND_PCM_CH2 );
		//	//SND_startPlayPCM_XGM( SFX_STOP, 1, SOUND_PCM_CH2 );
		//}

		VDP_waitVSync();
	}

	return 0;
}

