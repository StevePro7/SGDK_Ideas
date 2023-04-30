#include "main.h"

#define ANIM_STAND      0
#define ANIM_WAIT       1
#define ANIM_WALK       2
#define ANIM_RUN        3
#define ANIM_BRAKE      4
#define ANIM_UP         5
#define ANIM_CROUNCH    6
#define ANIM_ROLL       7

static void handleInput();

Sprite *mi_sonic;

s16 posx = 64;
s16 posy = 155;

int main()
{
	VDP_setScreenWidth320();

	u16 ind;

	u16* data1 = NULL;
	u16* data2 = NULL;

	u16 numTile = 0;
#ifndef _CONSOLE
	data1 = fondo2.palette->data;
	data2 = sonic_sprite.palette->data;
#endif

	VDP_setPalette( PAL1, data1 );
	VDP_setPalette( PAL0, data2 );
	ind = 1;
	VDP_drawImageEx( BG_B, &fondo2, TILE_ATTR_FULL( PAL1, 1, 0, -0, ind ), 0, 0, 1, CPU );

#ifndef _CONSOLE
	numTile = fondo2.tileset->numTile;
#endif
	ind += numTile;

	SPR_init( 0, 0, 0 );
	mi_sonic = SPR_addSprite( &sonic_sprite, posx, posy, TILE_ATTR( PAL0, TRUE, FALSE, FALSE ) );

	VDP_setTextPalette( PAL1 );

	VDP_drawText( "Pulsa A  -  Sonic SIN PRIORIDAD       ", 1, 0 );
	VDP_drawText( "Pulsa B  -  Sonic CON PRIORIDAD       ", 1, 1 );
	while( 1 )
	{
		handleInput();

		SPR_update();

		VDP_waitVSync();
	}

	return 0;
}


static void handleInput()
{
	u16 value = JOY_readJoypad( JOY_1 );

	if( value & BUTTON_LEFT )
	{
		SPR_setPosition( mi_sonic, posx--, posy );
		SPR_setHFlip( mi_sonic, TRUE );
		SPR_setAnim( mi_sonic, ANIM_RUN );
	}
		if( value & BUTTON_RIGHT )
	{
		SPR_setPosition( mi_sonic, posx++, posy );
		SPR_setHFlip( mi_sonic, FALSE );
		SPR_setAnim( mi_sonic, ANIM_RUN );
	}

	if( value & BUTTON_A )
	{
		SPR_setPriorityAttribut( mi_sonic, FALSE );
	}
		if( value & BUTTON_B )
	{
		SPR_setPriorityAttribut( mi_sonic, TRUE );
	}

	if( ( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_LEFT ) ) )
	{
		SPR_setAnim( mi_sonic, ANIM_STAND );
	}
}