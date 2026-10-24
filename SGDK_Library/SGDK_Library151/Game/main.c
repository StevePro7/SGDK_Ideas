#include "main.h"

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	if( joy != JOY_1 )
	{
		return;
	}

	if( state & changed & BUTTON_A )
	{
	}
}

int main()
{
	u8 num = 9;
//	u8 test;
	//u8 test = z80_vgm[ 2 ];
	u8 code = HALT_Z80_ON_DMA;
	u16 big = 300;
	u32 value;

	char buffer[ 10 ] = "STEVE PRO\0";

	VAR2REG_B( 1, 2 );

	VRAM_releaseRegion( NULL );
	XGM_resumePlay();
	YM2612_enableDAC();
	Z80_init();

	JOY_init();
	JOY_setEventHandler( myJoyHandler );

	//test = evd_mmcInit();

	SND_stopPlay_PCM();

	fix16ToStr( 1, buffer, 2 );

	MEM_pack();

	big = getLog2Int( 7 );

	M3D_buildMat3D( NULL );

	PAL_waitFadeCompletion();

	PSG_init();

	SYS_disableInts();
	SYS_enableInts();

	value = getTick();

	//test = fat16Init();

	DMA_init();
	VDP_clearSprites();
	VDP_interruptFade();

	VDP_doVRamDMACopy( 1, 2, 3 );
	BMP_clear();

	big = SYS_getBank( 7 );

	SPR_clear();

	SRAM_disable();
	SRAM_enable();

	qsort_s32( NULL, 10, 20 );
	return 0;
}