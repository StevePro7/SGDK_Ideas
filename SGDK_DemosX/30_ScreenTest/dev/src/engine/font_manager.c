#include "font_manager.h"

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

#define MAX_CHAR	5
char str_score[ MAX_CHAR ] = "0";

void engine_font_manager_clear( unsigned int x, unsigned int y, unsigned int w )
{
	VDP_clearText( x, y, w );
}

// http://gendev.spritesmind.net/forum/viewtopic.php?t=3093
void engine_font_manager_data( unsigned int value, unsigned int x, unsigned int y )
{
	// Set '5' = MAX_CHAR to get right aligned.
	sprintf( str_score, "%5d", value );
	VDP_clearText( x, y, MAX_CHAR );
	VDP_drawText( str_score, x, y );
}

void engine_font_manager_text( const char *str, unsigned int x, unsigned int y )
{
	VDP_drawText( str, x, y );
}