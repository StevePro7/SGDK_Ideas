#include "main.h"

// extern assembly methods
//#ifdef ENABLE_ASM
void bench_add8reg( u16 len );
//#endif


void executeMathsBasicTest()
{
#ifdef ENABLE_ASM
	bench_add8reg( i );
#endif
}

int main()
{
	u8 d8 = 12;
	engine_font_manager_data( d8, 10, 5 );
	//executeMathsBasicTest();
	VDP_drawText( "HELLO WORLD", 10, 10 );

	while( 1 )
	{
		VDP_waitVSync();
	}

	return 0;
}

