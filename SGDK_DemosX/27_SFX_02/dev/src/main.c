#include "main.h"

int main()
{
	unsigned char input;
	//int sizes[] = { 38656 ,69376, 6144 ,218368 };
	const u8 *audio;
	u8 index;
	unsigned int sized;

	VDP_drawText( "START  : TEST", 5, 1 );
	VDP_drawText( "STOP   : DOWN", 5, 2 );
	VDP_drawText( "PAUSE  : LEFT", 5, 3 );
	VDP_drawText( "RESUME : RGHT", 5, 4 );


	for( index = 0; index < 4; index++ )
	{
		audio = myaudio[ index ];
		//sized = sizes[ index ];
		//sized = sizeof( *audio );
		sized = strlen( audio );
		engine_font_manager_data( sized, 10, 15 + index );
		//SND_setPCM_XGM( SFX_DEAD + index, audio, sizes[index] );
		SND_setPCM_XGM( SFX_DEAD + index, audio, sized );
	}

	//VDP_drawText( "PRESSED: TEST", 5, 10 );
	while( 1 )
	{
		engine_input_manager_update();

		input = engine_input_manager_hold_buttonA();
		if( input )
		{
			VDP_drawText( "PRESSED: NICE", 5, 10 );

			//SND_startPlayPCM_XGM( SFX_DEAD, 1, SOUND_PCM_CH2 );
			XGM_startPlayPCM( SFX_KILL, 1, SOUND_PCM_CH2 );
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

