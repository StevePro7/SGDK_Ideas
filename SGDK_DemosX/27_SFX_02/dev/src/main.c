#include "main.h"

#define MAX_SONGS	32

int main()
{
	unsigned char input;
	//int sizes[] = { 38656, 69376, 6144, 218368 };
	const u8 *audio;
	u8 index;
	unsigned int sized;

	VDP_drawText( "START  : TEST", 5, 1 );
	VDP_drawText( "STOP   : DOWN", 5, 2 );
	VDP_drawText( "PAUSE  : LEFT", 5, 3 );
	VDP_drawText( "RESUME : RGHT", 5, 4 );


	for( index = 0; index < MAX_SONGS; index++ )
	{
		audio = myaudio[ index ];

		// https://www.geeksforgeeks.org/how-to-find-size-of-array-in-cc-without-using-sizeof-operator
		//sized = *( &myaudio[ index ] + 1 ) - myaudio[ index ];
		//sized = *( &myaudio[ index ] + (index+1) ) - myaudio[ index ];
		//const u8 *p1 = *( &myaudio[ index + 1 ] );
		//const u8 *p0 = *( &myaudio[ index  ] );
		//sized = p1 - p0;

		sized = myaudio_size[ index ];
		
		//sized = strlen( audio );
		//engine_font_manager_data( sized, 10, 15 + index );
		//SND_setPCM_XGM( SFX_DEAD + index, audio, sizes[index] );
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

		input = engine_input_manager_hold_up();
		if( input )
		{
			index++;
			if( index >= MAX_SONGS )
			{
				index = 0;
			}

			engine_font_manager_data( (index+1), 20, 5 );
		}
		input = engine_input_manager_hold_down();
		if( input )
		{
			if( index <= 0 )
			{
				index = 32;
			}

			index--;
			engine_font_manager_data( ( index + 1 ), 20, 5 );
		}

		VDP_waitVSync();
	}

	return 0;
}

