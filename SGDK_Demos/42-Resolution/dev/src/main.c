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
	u16 x = 256 / 8 - 4;
	u16 y = 224 / 8 - 1;

	//int score = 420;
	u16 wide = 0;
	u16 high = 0;

	wide = VDP_getScreenWidth();
	high = VDP_getScreenHeight();

	updateScoreDisplay( wide, 2, 1 );
	updateScoreDisplay( high, 2, 2 );

	//VDP_setScreenHeight240();
	VDP_setScreenWidth256();

	wide = VDP_getScreenWidth();
	high = VDP_getScreenHeight();

	updateScoreDisplay( wide, 2, 5 );
	updateScoreDisplay( high, 2, 6 );

	VDP_drawText( "test", x, y );
	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

