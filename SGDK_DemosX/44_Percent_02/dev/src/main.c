#include "main.h"

char str_score[ 3 ] = "0";

void updateScoreDisplay(u16 value, u16 x, u16 y)
{
	//sprintf( str_score, "%d", score );
	sprintf( str_score, "%d", value );
	VDP_clearText( x, y, 3 );
	VDP_drawText( str_score, x, y );
}

int main()
{
	unsigned char score;
	unsigned char maxim;
	unsigned short percent;

	score = 0;
	maxim = 0;
	//if( 0 == maxim )
	//{
	//	percent = 0;
	//}
	//else
	//{
	//	percent = ( float ) score / ( float ) maxim * 100;
	//}

	percent = 0 == maxim ? 0 : ( float ) score / ( float ) maxim * 100;

	updateScoreDisplay( percent, 10, 10 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

