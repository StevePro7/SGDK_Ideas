#include "font_manager.h"

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

#define MAX_CHAR	5
char str_data[ MAX_CHAR ] = "0";
char str_char[ 1 ] = "0";

void engine_font_manager_clear( unsigned short x, unsigned short y, unsigned short w )
{
	VDP_clearText( x, y, w );
}

// http://gendev.spritesmind.net/forum/viewtopic.php?t=3093
void engine_font_manager_data( unsigned short value, unsigned short x, unsigned short y )
{
	// Set '5' = MAX_CHAR to get right aligned.
	sprintf( str_data, "%5d", value );
	VDP_clearText( x, y, MAX_CHAR );
	VDP_drawText( str_data, x, y );
}

void engine_font_manager_char( const char ch, unsigned short x, unsigned short y )
{
	sprintf( str_char, "%c", ch );
	VDP_drawText( str_char, x, y );
}

void engine_font_manager_text( const char *str, unsigned short x, unsigned short y )
{
	VDP_drawText( str, x, y );
}