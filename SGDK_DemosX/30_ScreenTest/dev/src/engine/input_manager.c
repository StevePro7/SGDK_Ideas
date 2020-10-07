#include "input_manager.h"

#ifdef _CONSOLE
#include "_genesis.h"
#else
#include <genesis.h>
#endif

// Must be static to persist values!
static unsigned int curr_joypad1 = 0;
static unsigned int prev_joypad1 = 0;

// Private helper methods.
static unsigned char engine_input_manager_hold( unsigned int data );
static unsigned char engine_input_manager_move( unsigned int data );

// Public method.
void engine_input_manager_update()
{
	prev_joypad1 = curr_joypad1;
	curr_joypad1 = JOY_readJoypad( JOY_1 );
}

// Public methods HOLD.
unsigned char engine_input_manager_hold_up()
{
	return engine_input_manager_hold( BUTTON_UP );
}
unsigned char engine_input_manager_hold_down()
{
	return engine_input_manager_hold( BUTTON_DOWN );
}
unsigned char engine_input_manager_hold_left()
{
	return engine_input_manager_hold( BUTTON_LEFT );
}
unsigned char engine_input_manager_hold_right()
{
	return engine_input_manager_hold( BUTTON_RIGHT );
}
unsigned char engine_input_manager_hold_buttonA()
{
	return engine_input_manager_hold( BUTTON_A );
}
unsigned char engine_input_manager_hold_buttonB()
{
	return engine_input_manager_hold( BUTTON_B );
}
unsigned char engine_input_manager_hold_buttonC()
{
	return engine_input_manager_hold( BUTTON_C );
}
unsigned char engine_input_manager_hold_buttonStart()
{
	return engine_input_manager_hold( BUTTON_START );
}

// Public methods MOVE.
unsigned char engine_input_manager_move_up()
{
	return engine_input_manager_move( BUTTON_UP );
}
unsigned char engine_input_manager_move_down()
{
	return engine_input_manager_move( BUTTON_DOWN );
}
unsigned char engine_input_manager_move_left()
{
	return engine_input_manager_move( BUTTON_LEFT );
}
unsigned char engine_input_manager_move_right()
{
	return engine_input_manager_move( BUTTON_RIGHT );
}
unsigned char engine_input_manager_move_buttonA()
{
	return engine_input_manager_move( BUTTON_A );
}
unsigned char engine_input_manager_move_buttonB()
{
	return engine_input_manager_move( BUTTON_B );
}
unsigned char engine_input_manager_move_buttonC()
{
	return engine_input_manager_move( BUTTON_C );
}
unsigned char engine_input_manager_move_buttonStart()
{
	return engine_input_manager_move( BUTTON_START );
}

// Private helper methods.
static unsigned char engine_input_manager_hold( unsigned int data )
{
	return curr_joypad1 & data && !( prev_joypad1 & data );
}
static unsigned char engine_input_manager_move( unsigned int data )
{
	return curr_joypad1 & data;
}