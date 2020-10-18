#include "font_manager.h"

#define MAX_CHAR	8
char str_score[ MAX_CHAR ] = "0";

// http://gendev.spritesmind.net/forum/viewtopic.php?t=3093
void engine_font_manager_data( unsigned int value, u16 x, u16 y )
{
	sprintf( str_score, "%8d", value );
	VDP_clearText( x, y, MAX_CHAR );
	VDP_drawText( str_score, x, y );
}