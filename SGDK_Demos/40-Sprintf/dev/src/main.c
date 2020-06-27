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
	//int score = 420;
	u16 wide = 0;
	u16 high = 0;

	wide = VDP_getScreenWidth();
	high = VDP_getScreenHeight();

	updateScoreDisplay( wide, 2, 1 );
	updateScoreDisplay( high, 2, 2 );

	VDP_setScreenHeight240();

	wide = VDP_getScreenWidth();
	high = VDP_getScreenHeight();

	updateScoreDisplay( wide, 2, 5 );
	updateScoreDisplay( high, 2, 6 );

	VDP_drawText( "hello", 10, 10 );


	updateScoreDisplay( wide, 2, 1 );
	updateScoreDisplay( high, 2, 2 );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

