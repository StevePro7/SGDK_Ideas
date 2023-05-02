#include "main.h"

static void handleInput();
void myJoyHandler( u16 joy, u16 changed, u16 state );
void reset();

Sprite *mi_sonic;
s16 mi_sonic_posx = 64;
s16 mi_sonic_posy = 155;

Sprite *mi_barra;
s16 mi_barra_posx = 120;
s16 mi_barra_posy = 96;

int estado = 0;
u16 ind;
u16 numTile2 = 0;

int main()
{
	u16 * data1 = NULL;
	u16 * data2 = NULL;
	u16 * data3 = NULL;
	u16 numTile1 = 0;
	

#ifndef _CONSOLE
	data1 = fondo1.palette->data;
	numTile1 = fondo1.tileset->numTile;
	data2 = sonic_sprite.palette->data;
	data3 = barra_sprite.palette->data;
	numTile2 = fondo2.tileset->numTile;
#endif
	VDP_setScreenWidth320();

	SPR_init( 0, 0, 0 );

	VDP_setPalette( PAL0, data1 );

	ind = TILE_USERINDEX;
	VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, FALSE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
	ind += numTile1;

	VDP_setPalette( PAL1, data2 );
	VDP_setPalette( PAL2, data3 );
	VDP_setPalette( PAL3, data3 );

	mi_barra = SPR_addSprite( &barra_sprite, mi_barra_posx, mi_barra_posy, TILE_ATTR( PAL2, FALSE, FALSE, FALSE ) );

	mi_sonic = SPR_addSprite( &sonic_sprite, mi_sonic_posx, mi_sonic_posy, TILE_ATTR( PAL3, FALSE, FALSE, FALSE ) );

	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

	//Texto inicial
	VDP_drawText( "PRUEBA  0", 1, 0 );
	VDP_drawText( "-Pulsa A para seguir-", 1, 27 );
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
	//variable donde se guarda la entrada del mando
	u16 value = JOY_readJoypad( JOY_1 );
	//si pulsamos izquierda...
	if( value & BUTTON_LEFT )
		SPR_setPosition( mi_barra, mi_barra_posx--, mi_barra_posy );
	//si pulsamos derecha...
	if( value & BUTTON_RIGHT )
		SPR_setPosition( mi_barra, mi_barra_posx++, mi_barra_posy );
	//si pulsamos arriba...
	if( value & BUTTON_UP )
		SPR_setPosition( mi_barra, mi_barra_posx, mi_barra_posy-- );
	//si pulsamos abajo...
	if( value & BUTTON_DOWN )
		SPR_setPosition( mi_barra, mi_barra_posx, mi_barra_posy++ );
}

void myJoyHandler( u16 joy, u16 changed, u16 state )
{
	if( joy == JOY_1 )
	{
		if( estado == 0 && changed & BUTTON_A )
		{
			estado = 1;
			VDP_drawText( "PRUEBA 01", 1, 0 );
			VDP_drawText( "-Pulsa B para seguir-", 1, 27 );
			VDP_setHilightShadow( 1 );
		}

		if( estado == 1 && ( changed & BUTTON_B ) )
		{
			estado = 2;
			VDP_drawText( "PRUEBA 02", 1, 0 );
			VDP_drawText( "-Pulsa C para seguir-", 1, 27 );
			SPR_setPriorityAttribut( mi_sonic, TRUE );
			SPR_setPriorityAttribut( mi_barra, FALSE );
		}

		if( estado == 2 && ( changed & BUTTON_C ) )
		{
			estado = 3;
			VDP_drawText( "PRUEBA 03", 1, 0 );
			VDP_drawText( "-Pulsa A para seguir-", 1, 27 );
			SPR_setPriorityAttribut( mi_sonic, FALSE );
			SPR_setPriorityAttribut( mi_barra, TRUE );
		}

		if( estado == 3 && ( changed & BUTTON_A ) )
		{
			estado = 4;
			VDP_drawText( "PRUEBA 04", 1, 0 );
			VDP_drawText( "-Pulsa B para seguir-", 1, 27 );
			SPR_setPriorityAttribut( mi_sonic, FALSE );
			SPR_setPriorityAttribut( mi_barra, FALSE );
			SPR_setPalette( mi_barra, PAL3 );
		}

		//ESTADO 05:

		if( estado == 4 && ( changed & BUTTON_B ) )
		{
			estado = 5;
			VDP_drawText( "PRUEBA 05", 1, 0 );
			VDP_drawText( "-Pulsa C para seguir-", 1, 27 );
			SPR_setPriorityAttribut( mi_barra, TRUE );
		}

		if( estado == 5 && ( changed & BUTTON_C ) )
		{
			estado = 6;
			//volvemos a dibujar el fondo, ahora con prioridad
			ind = TILE_USERINDEX;
			VDP_drawImageEx( BG_A, &fondo1, TILE_ATTR_FULL( PAL0, TRUE, FALSE, FALSE, ind ), 0, 0, FALSE, TRUE );
			ind += numTile2;
			VDP_drawText( "PRUEBA 06", 1, 0 );
			VDP_drawText( "-Pulsa A para seguir-", 1, 27 );
			SPR_setPriorityAttribut( mi_sonic, FALSE );
			SPR_setPriorityAttribut( mi_barra, FALSE );
		}

		if( estado == 6 && ( changed & BUTTON_A ) )
		{
			estado = 7;
			VDP_drawText( "PRUEBA 07", 1, 0 );
			VDP_drawText( "-Pulsa B para seguir-", 1, 27 );
			//movemos a Sonic a una posición más visible
			SPR_setPosition( mi_sonic, mi_sonic_posx - 30, mi_sonic_posy );
		}

		//ESTADO 08:

		if( estado == 7 && ( changed & BUTTON_B ) )
		{
			estado = 8;
			VDP_drawText( "PRUEBA 08", 1, 0 );
			VDP_drawText( "-Pulsa C para reiniciar-", 1, 27 );
			SPR_setPriorityAttribut( mi_sonic, TRUE );
			SPR_setPriorityAttribut( mi_barra, TRUE );
		}

		if( estado == 8 && ( changed & BUTTON_C ) )
			reset();
	}
}

void reset()
{
	SYS_hardReset();
}