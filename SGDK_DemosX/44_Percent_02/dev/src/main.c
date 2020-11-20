#include "main.h"

//char str_score[ 3 ] = "0";
//
//void updateScoreDisplay(u16 value, u16 x, u16 y)
//{
//	//sprintf( str_score, "%d", score );
//	sprintf( str_score, "%3d", value );
//	VDP_clearText( x, y, 3 );
//	VDP_drawText( str_score, x, y );
//}

int main()
{
	unsigned char score_correct;
	unsigned char score_answerd;
	unsigned short saved_correct;
	unsigned short saved_answerd;
	unsigned short percent;

	//score_correct = 1;
	score_answerd = 40;
	for( score_correct = 0; score_correct <= 20; score_correct++ )
	{
		percent = score_correct * 100 / score_answerd;
		//updateScoreDisplay( percent, 10,  score_correct - 20);
		//engine_font_manager_zero( percent, 10, score_correct - 20 );
		engine_font_manager_data( percent, 10, score_correct - 0 );
	}
	for( score_correct = 20; score_correct <= score_answerd; score_correct++ )
	{
		percent = score_correct * 100 / score_answerd;
		//updateScoreDisplay( percent, 10,  score_correct - 20);
		//engine_font_manager_zero( percent, 10, score_correct - 20 );
		engine_font_manager_data( percent, 30, score_correct - 20 );
	}
	
	saved_correct = 65534;
	saved_answerd = 65535;
	percent = saved_correct * 100 / saved_answerd;
	engine_font_manager_data( percent, 15, 24 );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

