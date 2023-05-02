#include "main.h"

#define ANIM_STAND      0
#define ANIM_WALK       1

static void handleInput();

Sprite* spr_ryu;
Sprite* spr_sombra;
Sprite* spr_hadoken;

s16 posx = 120;
s16 posy = 120;
s16 hadoken_posx = 150;
s16 hadoken_posy = 130;

bool prioridad_hadoken = TRUE;

int main()
{
	u16 ind;

	u16 *data1 = NULL;
	u16 *data2 = NULL;
	u16 *data3 = NULL;
	u16 *data4 = NULL;
	u16 numTile1 = 0;
	u16 numTile2 = 0;
#ifndef _CONSOLE
	data1 = fondo1.palette->data;
	data2 = fondo1.palette->data;
	numTile1 = fondo1.tileset->numTile;
	numTile2 = fondo2.tileset->numTile;
	data3 = mi_sprite_ryu.palette->data;
	data4 = mi_sprite_sombra.palette->data;
#endif

	VDP_setScreenWidth320();

	SPR_init( 0, 0, 0 );

	VDP_setPalette( PAL0, data1 );
	VDP_setPalette( PAL1, data2 );

	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, TRUE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile1;
	VDP_drawImageEx( BG_B, &fondo2, TILE_ATTR_FULL( PAL1, TRUE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile2;

	VDP_setPalette( PAL2, data3 );
	VDP_setPalette( PAL3, data4 );

	spr_ryu = SPR_addSprite( &mi_sprite_ryu, posx, posy, TILE_ATTR( PAL2, TRUE, FALSE, FALSE ) );
	spr_sombra = SPR_addSprite( &mi_sprite_sombra, posx, posy + 70, TILE_ATTR( PAL3, TRUE, FALSE, FALSE ) );
	spr_hadoken = SPR_addSprite( &mi_sprite_hadoken, hadoken_posx, hadoken_posy, TILE_ATTR( PAL3, prioridad_hadoken, FALSE, FALSE ) );

	VDP_setHilightShadow( 1 );

	SPR_setHFlip( spr_ryu, TRUE );
	SPR_setHFlip( spr_hadoken, TRUE );

	VDP_setTextPalette( PAL3 );
	VDP_drawText( "SHADOW & HIGHLIGHT : SF2                ", 2, 1 );
	VDP_drawText( "D-PAD: MOV RYU, A/B: MOV HA-DO-KEN      ", 2, 2 );

	SPR_update();
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
		SPR_setPosition( spr_ryu, posx--, posy );
		SPR_setPosition(spr_sombra, posx, posy + 70 );
		SPR_setAnim( spr_ryu, ANIM_WALK );
		SPR_setHFlip( spr_ryu, FALSE );
	}

	if( value & BUTTON_RIGHT )
	{
		SPR_setPosition( spr_ryu, posx++, posy );
		SPR_setPosition( spr_sombra, posx++, posy + 70 );
		SPR_setAnim( spr_ryu, ANIM_WALK );
		SPR_setHFlip( spr_ryu, TRUE );
	}

	if( value & BUTTON_UP )
		SPR_setPosition( spr_ryu, posx, posy-- );
	//si pulsamos abajo...
	if( value & BUTTON_DOWN )
		SPR_setPosition( spr_ryu, posx, posy++ );

	if( value & BUTTON_A )
		SPR_setPosition( spr_hadoken, hadoken_posx++, hadoken_posy );
	//si pulsamos B
	if( value & BUTTON_B )
		SPR_setPosition( spr_hadoken, hadoken_posx--, hadoken_posy );

	if( ( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_LEFT ) ) )
	{
		SPR_setAnim( spr_ryu, ANIM_STAND );
	}
}