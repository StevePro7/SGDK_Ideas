#include "main.h"

#define ANIM_STAND      0
#define ANIM_RUN        3

static void handleInput();

static void mueveEnemigos();

static void pinta_posicion();

Sprite *mi_sonic;

int posx = 64;
int posy = 155;

Sprite *enemigo[ 2 ];

u16 enemigoPosx[ 2 ];
int enemigoPosy[ 2 ];
int enemigoSentidoMovimiento;

#define CONST 84

int main()
{
	u16 ind;

	u16* data1 = NULL;
	u16* data2 = NULL;
	u16* data3 = NULL;
	u16* data4 = NULL;

	u16 numTile1 = 0;
	u16 numTile2 = 0;

	VDP_setScreenWidth320();
	SPR_init( 0, 0, 0 );

#ifndef _CONSOLE
	data1 = fondo1.palette->data;
	data2 = fondo2.palette->data;
	data3 = sonic_sprite.palette->data;
	data4 = enemies_sprite.palette->data;

	numTile1 = fondo1.tileset->numTile;
	numTile2 = fondo2.tileset->numTile;
#endif

	VDP_setPalette( PAL0, data1 );
	VDP_setPalette( PAL1, data2 );

	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_B, &fondo1, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile1;
	VDP_drawImageEx( BG_A, &fondo2, TILE_ATTR_FULL( PAL1, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile2;

	VDP_setPalette( PAL2, data3 );
	mi_sonic = SPR_addSprite( &sonic_sprite, posx, posy, TILE_ATTR( PAL2, TRUE, FALSE, FALSE ) );

	enemigoPosx[ 0 ] = 128;
	enemigoPosy[ 0 ] = 164;
	enemigoPosx[ 1 ] = 260;
	enemigoPosy[ 1 ] = 84;
	enemigoSentidoMovimiento = 1;

	VDP_setPalette( PAL3, data4 );

	enemigo[ 0 ] = SPR_addSprite( &enemies_sprite, enemigoPosx[ 0 ], enemigoPosy[ 0 ], TILE_ATTR( PAL3, TRUE, FALSE, FALSE ) );
	enemigo[ 1 ] = SPR_addSprite( &enemies_sprite, enemigoPosx[ 1 ], enemigoPosy[ 1 ], TILE_ATTR( PAL3, TRUE, FALSE, FALSE ) );
	
	SPR_setAnim( enemigo[ 0 ], 1 );
	SPR_setAnim( enemigo[ 1 ], 0 );
	SPR_update();

	while( 1 )
	{
		handleInput();

		mueveEnemigos();

		pinta_posicion();

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
		//SPR_setVFlip(mi_sonic, FALSE);
	}

	if( ( !( value & BUTTON_RIGHT ) ) && ( !( value & BUTTON_LEFT ) ) )
	{
		SPR_setAnim( mi_sonic, ANIM_STAND );
	}
}

static void mueveEnemigos()
{
	int velocidadmovx = 1;
	int acelerador = 1;
	int mod_amplitud = 1;

	enemigoPosx[ 0 ] += velocidadmovx * enemigoSentidoMovimiento;
	if( enemigoPosx[ 0 ] >= 320 || enemigoPosx[ 0 ] <= 0 )
		enemigoSentidoMovimiento *= -1;

	enemigoPosx[ 1 ] -= velocidadmovx;
	enemigoPosy[ 1 ] = CONST + sinFix16( enemigoPosx[ 1 ] * acelerador ) * mod_amplitud;

	SPR_setPosition( enemigo[ 0 ], enemigoPosx[ 0 ], enemigoPosy[ 0 ] );
	SPR_setPosition( enemigo[ 1 ], enemigoPosx[ 1 ], enemigoPosy[ 1 ] );
}

static void pinta_posicion()
{
	char cadena1[ 32 ];
	sprintf( cadena1, "Y(avispa):  %3d", enemigoPosy[ 1 ] );
	VDP_drawText( cadena1, 2, 2 );

}