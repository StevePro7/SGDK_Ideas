#include "main.h"

#define MAX_SONGS	1

int main()
{
	unsigned char input;
	u8 index;
	const u8 *audio;
	unsigned int sized;

	VDP_drawText( "START  : TEST", 5, 1 );
	VDP_drawText( "STOP   : DOWN", 5, 2 );
	VDP_drawText( "PAUSE  : LEFT", 5, 3 );
	VDP_drawText( "RESUME : RGHT", 5, 4 );


	for( index = 0; index < MAX_SONGS; index++ )
	{
		audio = myaudio[ index ];
		sized = myaudio_size[ index ];
		SND_setPCM_XGM( SFX_DEAD + index, audio, sized );
	}

	//VDP_drawText( "PRESSED: TEST", 5, 10 );
	index = 0;
	engine_font_manager_data( ( index + 1 ), 20, 5 );
	while( 1 )
	{
		engine_input_manager_update();

		input = engine_input_manager_hold_buttonA();
		if( input )
		{
			VDP_drawText( "PRESSED: NICE", 5, 10 );
			XGM_startPlayPCM( SFX_DEAD + index, 1, SOUND_PCM_CH2 );
		}
		input = engine_input_manager_hold_buttonB();
		if( input )
		{
			VDP_drawText( "PRESSED: STOP", 5, 10 );
			XGM_stopPlayPCM( SOUND_PCM_CH2 );
		}

		input = engine_input_manager_hold_up();
		if( input )
		{
			index++;
			if( index >= MAX_SONGS )
			{
				index = 0;
			}

			engine_font_manager_data( ( index + 1 ), 20, 5 );
		}
		input = engine_input_manager_hold_down();
		if( input )
		{
			if( index <= 0 )
			{
				index = MAX_SONGS;
			}

			index--;
			engine_font_manager_data( ( index + 1 ), 20, 5 );
		}

		VDP_waitVSync();
	}

	return 0;
}

