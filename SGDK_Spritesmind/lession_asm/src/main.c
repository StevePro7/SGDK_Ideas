#include "main.h"

static void handleInput();
static void reset();
#ifdef ENABLE_ASM
static void steveproreset();
#endif


int main()
{
	VDP_drawText( "SUZANNE", 8, 10 );
	while( 1 )
	{
		handleInput();
		VDP_waitVSync();
	}

	return 0;
}

static void handleInput()
{
	u16 value = JOY_readJoypad( JOY_1 );
	if( value & BUTTON_LEFT )
	{
		
		reset();
		VDP_drawText( "STEVEPRO", 8, 12 );
	}

	//if( ( !( value & BUTTON_UP ) ) && ( !( value & BUTTON_DOWN ) ) && ( !( value & BUTTON_LEFT ) ) &&
	//	( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_A ) ) && ( !( value & BUTTON_B ) ) &&
	//	( !( value & BUTTON_C ) ) && ( !( value & BUTTON_X ) ) && ( !( value & BUTTON_Y ) ) &&
	//	( !( value & BUTTON_Z ) ) && ( !( value & BUTTON_MODE ) ) && ( !( value & BUTTON_START ) ) )
	//{
	//	VDP_clearTextArea( 0, 7, 40, 23 );
	//}
}

void reset()
{
#ifdef ENABLE_ASM
	VDP_drawText( "BOBO2", 8, 14 );
	steveproreset();
#endif

//#ifndef _CONSOLE
//	asm( "move   #0x2700,%sr\n\t"
//		"move.l (0),%a7\n\t"
//		"move.l (4),%a0\n\t"
//		"jmp    (%a0)" );
//#endif
	//VDP_drawText( "IZQUIERDA", 8, 10 );
//#ifdef ENABLE_ASM
//	bench_add8reg( i );
//#endif
}

//void steveproreset()
//{
//}
