#include "main.h"

/// Counter to be incremented by background task
static volatile uint32_t count = 0;

/// Draw a hexadecimal number at specified coords
static void draw_hex( uint32_t value, uint16_t x, uint16_t y )
{
	char num[ 9 ];

	intToHex( value, num, 8 );
	num[ 8 ] = '\0';
	VDP_drawText( num, x, y );
}

/// Vertical interrupt callback, just increment and print frame count
static void vint_cb( void )
{
	static uint32_t frame_count = 0;

	draw_hex( frame_count++, 1, 1 );
}

/// Background task running in user mode. Will take all the available CPU
/// not used by the foreground task
static void bg_tsk( void )
{
	uint16_t posted = FALSE;
	while( TRUE ) {
		count++;
		if( !posted && count >= 0x100000 ) {
			posted = TRUE;
			TSK_superPost( FALSE );
		}
	}
}

/// Pend and print reason when resumed
static void pend_check( uint16_t timeout )
{
	const char *message;

	VDP_drawText( "PENDING ", 1, 3 );
	if( TSK_superPend( timeout ) ) {
		message = "TIMEOUT ";
	}
	else {
		message = "UNLOCKED";
	}
	VDP_drawText( message, 1, 3 );

}

/// Foreground task running in privileged mode. Will be awakened once per frame
static void fg_tsk( void )
{
	while( TRUE ) {
		draw_hex( count, 1, 2 );
		if( count > 0x10000 && count < 0x20000 ) {
			pend_check( 180 );
		}
		else if( count > 0x80000 && count < 0x90000 ) {
			pend_check( TSK_PEND_FOREVER );
		}
		else {
			SYS_doVBlankProcess();
		}
	}
}

/// Entry point
int main( bool hard )
{
	// Configure vertical blanking interrupt callback
	SYS_setVIntCallback( vint_cb );
	// Configure background task as user task
	TSK_userSet( bg_tsk );

	// Start foreground task
	fg_tsk();

	// We should never reach here
	return 0;
}

