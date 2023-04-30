#include "main.h"

static void handleInput();
static void pinta_posicion();

Sprite *mi_sprite_cuadrado;
Sprite *mi_sprite_sonic;
Sprite *mi_sprite;

int posx;
int posy;

int main()
{
	posx = 0;
	posy = 0;

	u16* data = NULL;

#ifndef _CONSOLE
	data = sprite_8x8.palette->data;
#endif

	VDP_setScreenWidth320();

	SPR_init( 0, 0, 0 );

	VDP_setPalette( PAL1, data );

	mi_sprite_cuadrado = SPR_addSprite( &sprite_8x8, posx, posy, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );
	mi_sprite_sonic = SPR_addSprite( &sprite_sonic, posx, posy, TILE_ATTR( PAL1, TRUE, FALSE, FALSE ) );

	mi_sprite = mi_sprite_cuadrado;
	while( 1 )
	{
		handleInput();

		pinta_posicion();

		SPR_update();

		VDP_waitVSync();
	}

	return 0;
}


static void handleInput()
{
	//variable donde se guarda la entrada del mando
	u16 value = JOY_readJoypad( JOY_1 );
	//si pulsamos izquierda...
	if( value & BUTTON_LEFT )
		SPR_setPosition( mi_sprite, posx--, posy );
	//si pulsamos derecha...
	if( value & BUTTON_RIGHT )
		SPR_setPosition( mi_sprite, posx++, posy );
	//si pulsamos arriba...
	if( value & BUTTON_UP )
		SPR_setPosition( mi_sprite, posx, posy-- );
	//si pulsamos abajo...
	if( value & BUTTON_DOWN )
		SPR_setPosition( mi_sprite, posx, posy++ );

	//si pulsamos A...
	if( ( value & BUTTON_A ) && ( mi_sprite == mi_sprite_sonic ) ) {
		mi_sprite = mi_sprite_cuadrado;
		SPR_setPosition( mi_sprite, posx, posy ); //necesario para q actualice al momento la TV
	}
	//si pulsamos B...
	if( ( value & BUTTON_B ) && ( mi_sprite == mi_sprite_cuadrado ) ) {
		mi_sprite = mi_sprite_sonic;
		SPR_setPosition( mi_sprite, posx, posy );
	}
}

static void pinta_posicion()
{
	char cadena1[ 32 ];
	sprintf( cadena1, "x:  %4d", posx );
	VDP_drawText( cadena1, 2, 23 );

	char cadena2[ 32 ];
	sprintf( cadena2, "y:  %4d", posy );
	VDP_drawText( cadena2, 2, 24 );
}