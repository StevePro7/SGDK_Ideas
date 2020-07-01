#include "main.h"

enum GAME_STATE
{
	STATE_MENU,
	STATE_PLAY
};

enum GAME_STATE currentState;

void basicInit()
{
	JOY_init();
	currentState = STATE_MENU;
}

void joyHandlerMenu( u16 joy, u16 changed, u16 state )
{
	if( joy != JOY_1 )
	{
		return;
	}

	if( state & BUTTON_START & changed )
	{
		currentState = STATE_PLAY;
	}
}

void processStateMenu()
{
	//Init
	JOY_setEventHandler( joyHandlerMenu );

	VDP_setPaletteColor( 0, RGB24_TO_VDPCOLOR( 0x000000 ) );
	VDP_drawText( "MENU STATE", 10, 13 );

	//Update
	while( currentState == STATE_MENU )
	{
		VDP_waitVSync();
	}

	//Cleanup
	VDP_clearText( 10, 13, 10 );
}

void processStatePlay()
{
	u16 timer = 120;
	JOY_setEventHandler( NULL );

	VDP_setPaletteColor( 0, RGB24_TO_VDPCOLOR( 0x6dc2ca ) );
	VDP_drawText( "PLAY STATE", 10, 13 );

	while( currentState == STATE_PLAY )
	{
		timer--;
		if( timer == 0 )
		{
			currentState = STATE_MENU;
		}

		VDP_waitVSync();
	}

	//Cleanup
	VDP_clearText( 10, 13, 10 );
}

int main()
{
	basicInit();

	while( 1 )
	{
		switch( currentState )
		{
		case STATE_MENU:
		{
			processStateMenu();
			break;
		}
		case STATE_PLAY:
		{
			processStatePlay();
			break;
		}
		}
	}

	return 0;
}

